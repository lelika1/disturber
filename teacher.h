#ifndef TEACHER_H
#define TEACHER_H

#include "database.h"

#include <vector>

class Teacher {
public:
    Teacher(DataBase *_db, bool ruToDeDirection, size_t wordsCount, const QStringList &topicsList);

public:
    const QString* GetWord() const;
    bool SubmitAnswer(const QString &answer, QString &correctAnswer);
    bool GetRuToDe() const { return ruToDe; }

private:
    void ReadStudyEntries(std::vector<StudyEntry> &entries_);

private:
    DataBase *db;

    bool ruToDe;
    size_t wordsPerTraining;
    QStringList wordsTopicsList;

    size_t currentPairIndex;
    bool learnedByFirstTime;

    std::vector<StudyEntry> entries;
};

#endif // TEACHER_H
