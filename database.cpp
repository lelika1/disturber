#include <database.h>
#include <exception>
#include <iostream>

StudyEntry::StudyEntry(int _id, const QString &ru, const QString &de)
    : id(_id)
    , ruWord(ru)
    , deWord(de)
    , mistakesCount(-1)
{}

DataBase::DataBase(const QString &db_name) {
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(db_name);

    if (!sdb.open()) {
        qDebug() << "Open database failed. Error:" << sdb.lastError().text() << "\n";
        throw DBCreateException();
    }

    QString kCreateTableSql = "CREATE TABLE IF NOT EXISTS DICTIONARY("                  \
                              "ID    INTEGER   PRIMARY KEY   AUTOINCREMENT NOT NULL,"   \
                              "RU    TEXT                                  NOT NULL,"   \
                              "DE    TEXT                                  NOT NULL);";
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

void DataBase::LoadAllEntriesToModel(QSqlTableModel *model) {
    model->setTable("DICTIONARY");
    model->select();
}

void DataBase::LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart) {
    model->setTable("DICTIONARY");
    model->setFilter(QString("RU LIKE '%%1%' OR DE LIKE '%%1%'").arg(wordPart));
    model->select();
}
