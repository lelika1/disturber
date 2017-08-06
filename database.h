#pragma once

#include <vector>

#include <QtSql>

//typedef int (*SqliteCallback)(void *, int, char **, char **);

class DBCreateException: public std::exception {
public:
    virtual const char* what() const throw() {
        return "It is impossible to open DB or create table.";
    }
};

class DataBase {
public:
    DataBase(const QString &db_name);
    ~DataBase();
public:

//    struct TableEntry {
//        TableEntry(const int &id, const std::string &ru, const std::string &de);
//        int id_;
//        std::string ru_word_;
//        std::string de_word_;
//    };

public:
    int AddEntry(const QString &ru_word, const QString &de_word);
//    int DeleteEntry(const int &id);
//    int SelectAllEntries(std::vector<TableEntry> &entries);
    //void ShowAllEntries(QSqlQueryModel &model);
    void ShowAllEntries(QSqlTableModel *model);

public:
    QSqlDatabase sdb_;
};
