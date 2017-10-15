#include <database.h>
#include <exception>
#include <iostream>



StudyEntry::StudyEntry(int _id, const QString &ru, const QString &de,
                       int lastTime, double rate, int showDate)
    : id(_id)
    , ruWord(ru)
    , deWord(de)
    , lastTestDate(lastTime)
    , successRate(rate)
    , showAfterDate(showDate)
    , isDirty(false)
{}

DataBase::DataBase(const QString &db_name) {
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(db_name);

    if (!sdb.open()) {
        qDebug() << "Open database failed. Error:" << sdb.lastError().text() << "\n";
        throw DBCreateException();
    }

    QString kCreateTableSql = "CREATE TABLE IF NOT EXISTS DICTIONARY("                      \
                              "ID           INTEGER   PRIMARY KEY   AUTOINCREMENT NOT NULL,"\
                              "RU           TEXT                                  NOT NULL,"\
                              "DE           TEXT                                  NOT NULL,"\
                              "LASTDATE     INTEGER   DEFAULT 0,"                           \
                              "PROGRESS     REAL      DEFAULT 0.0,"                         \
                              "SHOWAFTER    INTEGER   DEFAULT 0);";

    QSqlQuery create_query;
    if (!create_query.exec(kCreateTableSql)) {
        sdb.close();
        std::cerr << "Create Table failed. Error:" << sdb.lastError().text().toStdString() << std::endl;
        throw DBCreateException();
    }
}

DataBase::~DataBase() {
    sdb.close();
}

int DataBase::AddEntry(const QString &ru_word, const QString &de_word) {
    QString add_str = "INSERT INTO DICTIONARY (RU,DE) VALUES ('%1', '%2');";
    add_str = add_str.arg(ru_word).arg(de_word);
    qDebug() << add_str << "\n";
    QSqlQuery add_query;
    if (!add_query.exec(add_str)) {
        qDebug() << "Add entry failed. Error:" << sdb.lastError().text() << "\n";
        return 1;
    }
    return 0;
}

int DataBase::SelectAllEntries(std::vector<StudyEntry> &entries) {
    QSqlQuery add_query;
    if (!add_query.exec("SELECT * FROM DICTIONARY;")) {
        qDebug() << "Select entries failed. Error:" << sdb.lastError().text() << "\n";
        return 1;
    }

    while (add_query.next()) {
        entries.emplace_back(StudyEntry(add_query.value(0).toInt(),
                                        add_query.value(1).toString(),
                                        add_query.value(2).toString(),
                                        add_query.value(3).toInt(),
                                        add_query.value(4).toDouble(),
                                        add_query.value(5).toInt()));
    }
    return 0;
}

int DataBase::UpdateEntries(const std::vector<StudyEntry> &entries) {
    for (auto &entry : entries) {
        if (entry.isDirty) {
            QString update_str = "UPDATE DICTIONARY SET PROGRESS='%1' WHERE ID='%2';";
            update_str = update_str.arg(entry.successRate).arg(entry.id);
            qDebug() << update_str << "\n";

            QSqlQuery update_query;
            if (!update_query.exec(update_str)) {
                qDebug() << "Update entry failed. Error:" << sdb.lastError().text() << "\n";
                return 1;
            }
        }
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
    QSqlQuery add_query;
    if (!add_query.exec("SELECT RU, DE FROM DICTIONARY;")) {
        qDebug() << "Select entries failed. Error:" << sdb.lastError().text() << "\n";
        return 1;
    }

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH:mm");
    csvPath = QDir::currentPath() + "/dictionary_" + currentTime + ".csv";
    QFile fileWriter(csvPath);
    fileWriter.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream textStream(&fileWriter);
    while (add_query.next()) {
        QString ru = add_query.value(0).toString();
        QString de = add_query.value(1).toString();
        textStream << ru << "," << de << '\n';
    }
    fileWriter.close();
    return 0;
}

