#pragma once

#include <QString>
#include <QtSql>

#include <vector>

struct StudyEntry {
    int id;
    QString ruWord;
    QString deWord;
    int mistakesCount;

    StudyEntry(int _id, const QString &ru, const QString &de);
};

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

    int ExportDictionaryToCSV(QString &csvPath);

public:
    QSqlDatabase sdb;
};
