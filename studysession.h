#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include "database.h"
#include "studyentry.h"
#include <vector>

class StudySession {
public:
    StudySession(DataBase *_db, bool ruToDeDirection, size_t wordsCount, const QStringList &topicsList);

public:
    const QString* GetWord() const;
    bool SubmitAnswer(const QString &answer, QString &correctAnswer);
    bool GetRuToDe() const { return ruToDe; }

private:
    void ReadStudyEntries(std::vector<StudyEntry> &entries_);

private:
    DataBase *db;

    bool ruToDe;
    size_t wordsPerSession;
    QStringList wordsTopicsList;

    size_t currentPairIndex;
    bool learnedByFirstTime;

    std::vector<StudyEntry> entries;
};

#endif // STUDYSESSION_H
