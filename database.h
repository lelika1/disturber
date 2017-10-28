#pragma once

#include <QString>
#include <QtSql>

#include <vector>

struct StudyEntry {
    int id;
    QString ruWord;
    QString deWord;
    int lastTestDate;
    double successRate;
    int showAfterDate;

    StudyEntry(int _id, const QString &ru, const QString &de,
               int lastTime = 0, double rate = 0, int showDate = 0);
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
    int SelectAllEntries(std::vector<StudyEntry> &entries);
    int UpdateEntry(const StudyEntry &entries);

    void LoadAllEntriesToModel(QSqlTableModel *model);
    void LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart);

    int ExportDictionaryToCSV(QString &csvPath);
    int ImportDictionaryFromCSV(const QString &csvPath);

public:
    QSqlDatabase sdb;
};
