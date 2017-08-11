#pragma once

#include <QtSql>

#include <vector>


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
    int AddEntry(const QString &ru_word, const QString &de_word);
    void LoadAllEntriesToModel(QSqlTableModel *model);
    void LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart);

public:
    QSqlDatabase sdb;
};
