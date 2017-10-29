#include <database.h>
#include <exception>
#include <iostream>

namespace {

int AddEntries(const QVariantList &ru_words, const QVariantList &de_words) {
    QSqlQuery q;
    q.prepare("INSERT INTO DICTIONARY (RU, DE)"
              " SELECT ?, ? WHERE NOT EXISTS"
              " (SELECT 1 FROM DICTIONARY WHERE ru = ? and de = ?)"
              ";");
    q.addBindValue(ru_words);
    q.addBindValue(de_words);
    q.addBindValue(ru_words);
    q.addBindValue(de_words);
    if (!q.execBatch()) {
        qDebug() << "AddEntries() failed:" << q.lastError().text();
        return 1;
    }
    return 0;
}

}

StudyEntry::StudyEntry(int _id, const QString &ru, const QString &de,
                       int lastTime, double rate, int showDate)
    : id(_id)
    , ruWord(ru)
    , deWord(de)
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

int DataBase::AddEntry(const QString &ru_word, const QString &de_word) {
    QVariantList ru_words;
    ru_words << ru_word.toLower();
    QVariantList de_words;
    de_words << de_word.toLower();
    return AddEntries(ru_words, de_words);
}

int DataBase::SelectByIds(const std::vector<int> &ids, std::vector<StudyEntry> &out) {
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
        out.emplace_back(StudyEntry(q.value(0).toInt(),
                                    q.value(1).toString(),
                                    q.value(2).toString(),
                                    q.value(3).toInt(),
                                    q.value(4).toDouble(),
                                    q.value(5).toInt()));
    }
    return 0;
}

int DataBase::SelectNOldest(size_t n, std::set<int> &ids) {
    QSqlQuery q;
    q.prepare("SELECT ID FROM DICTIONARY ORDER BY LASTDATE ASC LIMIT :N;");
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

int DataBase::SelectNWorstKnown(size_t n, std::set<int> &ids) {
    QSqlQuery q;
    q.prepare("SELECT ID FROM DICTIONARY ORDER BY PROGRESS ASC LIMIT :N;");
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

int DataBase::UpdateEntry(const StudyEntry &entry) {
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

int DataBase::ExportDictionaryToCSV(QString &csvPath) {
    QSqlQuery q;
    if (!q.exec("SELECT RU, DE FROM DICTIONARY;")) {
        qDebug() << "Select entries failed. Error:" << q.lastError().text();
        return 1;
    }

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH:mm");
    csvPath = QDir::currentPath() + "/dictionary_" + currentTime + ".csv";
    QFile fileWriter(csvPath);
    fileWriter.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream textStream(&fileWriter);
    while (q.next()) {
        QString ru = q.value(0).toString();
        QString de = q.value(1).toString();
        textStream << ru << "," << de << '\n';
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
    while (!in.atEnd()) {
        auto line = in.readLine().split(",");
        if (line.size() != 2) {
            qDebug() << "Incorrect line "<< line;
            break;
        }
        ru_words << line[0].toLower();
        de_words << line[1].toLower();
    }
    file.close();
    return AddEntries(ru_words, de_words);
}
