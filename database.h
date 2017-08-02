#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

typedef int (*SqliteCallback)(void *, int, char **, char **);

class DBCreateException: public std::exception {
public:
    virtual const char* what() const throw() {
        return "It is impossible to open DB or create table.";
    }
};

class DataBase {
public:
    DataBase(const char *db_name);
    ~DataBase();
public:

    struct TableEntry {
        TableEntry(const int &id, const std::string &ru, const std::string &de);
        int id_;
        std::string ru_word_;
        std::string de_word_;
    };

public:
    int AddEntry(const char *ru_word, const char *de_word);
    int DeleteEntry(const int &id);
    int SelectAllEntries(std::vector<TableEntry> &entries);

private:
    int SqliteExec(const std::string &func_name, const char *sql,
                   SqliteCallback callback = nullptr, void* callback_arg = nullptr);

private:
    sqlite3 *db_;
};
