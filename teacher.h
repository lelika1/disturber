#ifndef TEACHER_H
#define TEACHER_H

#include "database.h"

#include <vector>

class Teacher {
public:
    Teacher(DataBase *_db);
    ~Teacher();

public:
    bool InitStudy();
    bool GetNewPair(bool ruToDeDirection, QString &originalWord);
    bool CheckResult(bool ruToDeDirection, const QString &answer, QString &correctAnswer);

    void UpdateDBAfterStudy();

private:
    DataBase *db;
    size_t currentPairIndex;
    bool learnedByFirstTime;
    size_t successWordsInStudy;
    std::vector<StudyEntry> entries;
};

#endif // TEACHER_H
