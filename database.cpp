#include <database.h>
#include <exception>
#include <iostream>

int SelectEntryCallback(void *arg, int argc, char **argv, char **) {
    if (argc != 3) {
        return SQLITE_ERROR;
    }
    std::vector<DataBase::TableEntry>* vec = (std::vector<DataBase::TableEntry>*)arg;
    vec->emplace_back(atoi(argv[0]), argv[1], argv[2]);
    return SQLITE_OK;
}

DataBase::TableEntry::TableEntry(const int &id, const std::string &ru, const std::string &de)
    : id_(id)
    , ru_word_(ru)
    , de_word_(de)
{}

DataBase::DataBase(const char *db_name) {
    const char *kCreateTableSql = "CREATE TABLE IF NOT EXISTS DICTIONARY("                  \
                                  "ID    INTEGER   PRIMARY KEY   AUTOINCREMENT NOT NULL,"   \
                                  "RU    TEXT                                  NOT NULL,"   \
                                  "DE    TEXT                                  NOT NULL);";
    int rc = sqlite3_open(db_name, &db_);
    if (rc != SQLITE_OK) {
        std::cerr << "Open database failed. ErrCode:" << rc << ", ErrMsg:" << sqlite3_errmsg(db_) << std::endl;
        throw DBCreateException();
    }
    if ((rc = SqliteExec("CreateTable", kCreateTableSql, nullptr)) != SQLITE_OK) {
        sqlite3_close(db_);
        throw DBCreateException();
    }
}

DataBase::~DataBase() {
    sqlite3_close(db_);
}

int DataBase::SqliteExec(const std::string &func_name, const char *sql,
                         SqliteCallback callback, void *callback_arg)
{
    char *errMsg = 0;
    int rc = sqlite3_exec(db_, sql, callback, callback_arg, &errMsg);
    if (rc) {
        std::cerr << func_name << " failed. ErrCode:" << rc << ", ErrMsg:" << errMsg << std::endl;
        sqlite3_free(&errMsg);
    }
    return rc;
}

int DataBase::AddEntry(const char *ru_word, const char *de_word) {
    char sql[1024];
    sprintf(sql, "INSERT INTO DICTIONARY (RU,DE) VALUES ('%s', '%s');", ru_word, de_word);
    std::cout << sql << std::endl;
    return SqliteExec("AddEntry", sql);
}

int DataBase::DeleteEntry(const int &id) {
    char sql[1024];
    sprintf(sql, "DELETE FROM DICTIONARY WHERE ID=%d;", id);
    std::cout << sql << std::endl;
    return SqliteExec("DeleteEntry", sql);
}

int DataBase::SelectAllEntries(std::vector<DataBase::TableEntry> &entries) {
    return SqliteExec("SelectAllEntries", "SELECT ID, RU, DE FROM DICTIONARY", SelectEntryCallback, &entries);
}
