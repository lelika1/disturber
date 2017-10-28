#pragma once

#include <QString>
#include <QtSql>

#include <set>
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
    int SelectByIds(const std::set<int> &ids, std::vector<StudyEntry> &out);

    // Adds ids for N most likely forgotten words to a given ids set.
    int SelectNOldest(size_t n, std::set<int> &ids);
    // Adds ids for N words with lowest rate to a given ids set.
    int SelectNWorstKnown(size_t n, std::set<int> &ids);

    int UpdateEntry(const StudyEntry &entries);

    void LoadAllEntriesToModel(QSqlTableModel *model);
    void LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart);

    int ExportDictionaryToCSV(QString &csvPath);
    int ImportDictionaryFromCSV(const QString &csvPath);

public:
    QSqlDatabase sdb;
};
