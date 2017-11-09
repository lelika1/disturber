#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include "database.h"
#include <vector>
#include <ctime>

class StudyEntry: public DBEntry {
public:
    explicit StudyEntry(DBEntry e) : DBEntry(std::move(e)) {}

    QVariant data(int col, int role = Qt::DisplayRole) const;
    bool setData(int col, const QVariant & value, int role = Qt::EditRole);

public:
    std::time_t startTime = 0;
    std::time_t firstSubmissionTime = 0;
    size_t attempts = 0;
    QString firstAnswer = "";
    bool checked = false;
};

class StudySession : public QAbstractTableModel {
public:
    StudySession(DataBase *_db, bool ruToDeDirection, size_t wordsCount, const QStringList &topicsList);

    const QString* GetWord();
    bool SubmitAnswer(const QString &answer, QString &correctAnswer);
    bool GetRuToDe() const { return ruToDe; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;

private:
    void ReadStudyEntries(std::vector<StudyEntry> &entries_);

private:
    DataBase *db;

    bool ruToDe;
    size_t wordsPerSession;
    QStringList wordsTopicsList;

    size_t currentPairIndex;

    std::vector<StudyEntry> entries;
};

#endif // STUDYSESSION_H
