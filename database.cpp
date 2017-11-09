#include <database.h>
#include <exception>
#include <iostream>

namespace {

int AddEntries(const QVariantList &ru_words, const QVariantList &de_words, const QVariantList &topic) {
    QSqlQuery q;
    q.prepare("INSERT INTO DICTIONARY (RU, DE, TOPIC)"
              " SELECT ?, ?, ? WHERE NOT EXISTS"
              " (SELECT 1 FROM DICTIONARY WHERE ru = ? and de = ?)"
              ";");
    q.addBindValue(ru_words);
    q.addBindValue(de_words);
    q.addBindValue(topic);
    q.addBindValue(ru_words);
    q.addBindValue(de_words);
    if (!q.execBatch()) {
        qDebug() << "AddEntries() failed:" << q.lastError().text();
        return 1;
    }
    return 0;
}

}

DBEntry::DBEntry(int _id, const QString &ru, const QString &de, const QString &top,
                       int lastTime, double rate, int showDate)
    : id(_id)
    , ruWord(ru)
    , deWord(de)
    , topic(top)
    , lastTestDate(lastTime)
    , successRate(rate)
    , showAfterDate(showDate)
{}

DataBase::DataBase(const QString &db_name) {
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(db_name);

    if (!sdb.open()) {
        qDebug() << "Open database failed. Error:" << sdb.lastError().text();
        throw DBCreateException();
    }

    QString kCreateTableSql = "CREATE TABLE IF NOT EXISTS DICTIONARY("
                              "ID           INTEGER   PRIMARY KEY   AUTOINCREMENT NOT NULL,"
                              "RU           TEXT                                  NOT NULL,"
                              "DE           TEXT                                  NOT NULL,"
                              "TOPIC        TEXT      DEFAULT ANDERE              NOT NULL,"
                              "LASTDATE     INTEGER   DEFAULT 0,"
                              "PROGRESS     REAL      DEFAULT 0.5,"
                              "SHOWAFTER    INTEGER   DEFAULT 0);";

    QSqlQuery q;
    if (!q.exec(kCreateTableSql)) {
        sdb.close();
        std::cerr << "Create Table failed. Error:" << q.lastError().text().toStdString() << std::endl;
        throw DBCreateException();
    }
    // The following instructions should speed-up db operations.
    q.exec("PRAGMA synchronous = OFF");
    q.exec("PRAGMA journal_mode = MEMORY");
}

DataBase::~DataBase() {
    sdb.close();
}

int DataBase::AddEntry(const QString &ru_word, const QString &de_word, const QString &topic) {
    QVariantList ru_words;
    ru_words << ru_word.toLower();
    QVariantList de_words;
    de_words << de_word.toLower();
    QVariantList topics;
    topics << topic.toUpper();

    return AddEntries(ru_words, de_words, topics);
}

int DataBase::SelectByIds(const std::vector<int> &ids, std::vector<DBEntry> &out) {
    QStringList idstrings;
    for (int id : ids) {
        idstrings << QString::number(id);
    }
    QString numberlist = idstrings.join(",");

    QSqlQuery q;
    q.prepare("SELECT * FROM DICTIONARY WHERE ID in (" + numberlist + ");");

    if (!q.exec()) {
        qDebug() << "SelectByIds() failed:" << q.lastError().text();
        return 1;
    }
    while (q.next()) {
        out.emplace_back(DBEntry(q.value(0).toInt(),
                                    q.value(1).toString(),
                                    q.value(2).toString(),
                                    q.value(3).toString(),
                                    q.value(4).toInt(),
                                    q.value(5).toDouble(),
                                    q.value(6).toInt()));
    }
    return 0;
}

int DataBase::SelectNOldest(const QStringList &topicsList, size_t n, std::set<int> &ids) {
    QSqlQuery q;
    if ((topicsList.size() == 1 ) && (topicsList[0].toUpper() == "ALLES")) {
        q.prepare("SELECT ID FROM DICTIONARY ORDER BY LASTDATE ASC LIMIT :N;");
    } else {
        q.prepare("SELECT ID FROM DICTIONARY WHERE TOPIC in (" + topicsList.join(",") + ") ORDER BY LASTDATE ASC LIMIT :N;");
    }
    q.bindValue(":N", static_cast<int>(n));

    if (!q.exec()) {
        qDebug() << "SelectNOldest(" << n << ") failed with: " << q.lastError().text();
        return 1;
    }
    while (q.next()) {
        ids.insert(q.value(0).toInt());
    }
    return 0;
}

int DataBase::SelectNWorstKnown(const QStringList &topicsList, size_t n, std::set<int> &ids) {
    QSqlQuery q;
    if ((topicsList.size() == 1 ) && (topicsList[0].toUpper() == "ALLES")) {
        q.prepare("SELECT ID FROM DICTIONARY ORDER BY PROGRESS ASC LIMIT :N;");
    } else {
        q.prepare("SELECT ID FROM DICTIONARY WHERE TOPIC in (" + topicsList.join(",") + ") ORDER BY PROGRESS ASC LIMIT :N;");
    }
    q.bindValue(":N", static_cast<int>(n));

    if (!q.exec()) {
        qDebug() << "SelectNWorstKnown(" << n << ") failed with: " << q.lastError().text();
        return 1;
    }
    while (q.next()) {
        ids.insert(q.value(0).toInt());
    }
    return 0;
}

int DataBase::UpdateEntry(const DBEntry &entry) {
    QSqlQuery q;
    q.prepare("UPDATE DICTIONARY SET PROGRESS = :progress, LASTDATE = :lastdate WHERE ID = :id;");
    q.bindValue(":progress", entry.successRate);
    q.bindValue(":lastdate", entry.lastTestDate);
    q.bindValue(":id", entry.id);

    if (!q.exec()) {
        qDebug() << "Update entry failed. Error:" << q.lastError().text();
        return 1;
    }
    return 0;
}

void DataBase::LoadAllEntriesToModel(QSqlTableModel *model) {
    model->setTable("DICTIONARY");
    model->select();
}

void DataBase::LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart) {
    model->setTable("DICTIONARY");
    model->setFilter(QString("RU LIKE '%%1%' OR DE LIKE '%%1%'").arg(wordPart));
    model->select();
}

int DataBase::ExportDictionaryToCSV(const QString &csvPath) {
    QSqlQuery q;
    if (!q.exec("SELECT RU, DE, TOPIC FROM DICTIONARY;")) {
        qDebug() << "Select entries failed. Error:" << q.lastError().text();
        return 1;
    }

    QFile fileWriter(csvPath);
    fileWriter.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream textStream(&fileWriter);
    while (q.next()) {
        QString ru = q.value(0).toString();
        QString de = q.value(1).toString();
        QString topic = q.value(2).toString();
        textStream << ru << "," << de << "," << topic << '\n';
    }
    fileWriter.close();
    return 0;
}

int DataBase::ImportDictionaryFromCSV(const QString &csvPath) {
    QFile file(csvPath);
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    QVariantList ru_words;
    QVariantList de_words;
    QVariantList topics;
    while (!in.atEnd()) {
        auto line = in.readLine().split(",");
        if (line.size() != 3) {
            qDebug() << "Incorrect line "<< line;
            break;
        }
        ru_words << line[0].toLower();
        de_words << line[1].toLower();
        topics << line[2].toUpper();
    }
    file.close();
    return AddEntries(ru_words, de_words, topics);
}

int DataBase::GetTopicsList(QSet<QString> &topics) {
    QSqlQuery q;
    q.prepare("SELECT DISTINCT TOPIC FROM DICTIONARY ORDER BY TOPIC;");
    if (!q.exec()) {
        qDebug() << "GetTopicssList() failed with: " << q.lastError().text();
        return 1;
    }
    while (q.next()) {
        topics.insert(q.value(0).toString().toUpper());
    }
    return 0;
}
