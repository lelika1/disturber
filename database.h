#pragma once

#include <QString>
#include <QtSql>

#include <set>
#include <vector>

struct DBEntry {
    int id;
    QString ruWord;
    QString deWord;
    QString topic;
    int lastTestDate;
    double successRate;
    int showAfterDate;

    DBEntry(int _id, const QString &ru, const QString &de, const QString &top,
            int lastTime = 0, double rate = 0, int showDate = 0);
};

class DBCreateException: public std::exception {
public:
    const char* what() const throw() override {
        return "It is impossible to open DB or create table.";
    }
};


class DataBase {
public:
    DataBase(const QString &db_name);
    ~DataBase();

public:
    int AddEntry(const QString &ru_word, const QString &de_word, const QString &topic);
    int SelectByIds(const std::vector<int> &ids, std::vector<DBEntry> &out);

    // Adds ids for N most likely forgotten words to a given ids set.
    int SelectNOldest(const QStringList &topicsList, size_t n, std::set<int> &ids);
    // Adds ids for N words with lowest rate to a given ids set.
    int SelectNWorstKnown(const QStringList &topicsList, size_t n, std::set<int> &ids);

    int UpdateEntry(const DBEntry &entries);

    void LoadAllEntriesToModel(QSqlTableModel *model);
    void LoadEntriesWithFilter(QSqlTableModel *model, const QString &wordPart);

    int ExportDictionaryToCSV(const QString &csvPath);
    int ImportDictionaryFromCSV(const QString &csvPath);

    int GetTopicsList(QSet<QString> &topics);

public:
    QSqlDatabase sdb;
};
