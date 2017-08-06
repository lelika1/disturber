#include <database.h>
#include <exception>
#include <iostream>

//int SelectEntryCallback(void *arg, int argc, char **argv, char **) {
//    if (argc != 3) {
//        return SQLITE_ERROR;
//    }
//    std::vector<DataBase::TableEntry>* vec = (std::vector<DataBase::TableEntry>*)arg;
//    vec->emplace_back(atoi(argv[0]), argv[1], argv[2]);
//    return SQLITE_OK;
//}

//DataBase::TableEntry::TableEntry(const int &id, const std::string &ru, const std::string &de)
//    : id_(id)
//    , ru_word_(ru)
//    , de_word_(de)
//{}

DataBase::DataBase(const QString &db_name) {
    sdb_ = QSqlDatabase::addDatabase("QSQLITE");
    sdb_.setDatabaseName(db_name);

    if (!sdb_.open()) {
        qDebug() << "Open database failed. Error:" << sdb_.lastError().text() << "\n";
        throw DBCreateException();
    }

    QString kCreateTableSql = "CREATE TABLE IF NOT EXISTS DICTIONARY("                  \
                              "ID    INTEGER   PRIMARY KEY   AUTOINCREMENT NOT NULL,"   \
                              "RU    TEXT                                  NOT NULL,"   \
                              "DE    TEXT                                  NOT NULL);";
    QSqlQuery create_query;
    if (!create_query.exec(kCreateTableSql)) {
        sdb_.close();
        std::cerr << "Create Table failed. Error:" << sdb_.lastError().text().toStdString() << std::endl;
        throw DBCreateException();
    }
}

DataBase::~DataBase() {
    sdb_.close();
}

int DataBase::AddEntry(const QString &ru_word, const QString &de_word) {
    QString add_str = "INSERT INTO DICTIONARY (RU,DE) VALUES ('%1', '%2');";
    add_str = add_str.arg(ru_word).arg(de_word);
    qDebug() << add_str << "\n";
    QSqlQuery add_query;
    if (!add_query.exec(add_str)) {
        qDebug() << "Add entry failed. Error:" << sdb_.lastError().text() << "\n";
        return 1;
    }
    return 0;
}

void DataBase::ShowAllEntries(QSqlTableModel *model) {
    model->setTable("DICTIONARY");
    model->select();

//    model.setQuery("select * from DICTIONARY");
//    if (model.lastError().isValid()) {
//        qDebug() << "FAILED! " << model.lastError() << "\n";
//    }
}

//void DataBase::ShowAllEntries(QSqlQueryModel &model) {
//    model.setQuery("select * from DICTIONARY");
//    if (model.lastError().isValid()) {
//        qDebug() << "FAILED! " << model.lastError() << "\n";
//    }
//}


//int DataBase::DeleteEntry(const int &id) {
//    char sql[1024];
//    sprintf(sql, "DELETE FROM DICTIONARY WHERE ID=%d;", id);
//    std::cout << sql << std::endl;
//    return SqliteExec("DeleteEntry", sql);
//}

//int DataBase::SelectAllEntries(std::vector<DataBase::TableEntry> &entries) {
//    return SqliteExec("SelectAllEntries", "SELECT ID, RU, DE FROM DICTIONARY", SelectEntryCallback, &entries);
//}
