#ifndef TEACHER_H
#define TEACHER_H

#include "database.h"

#include <vector>

class Teacher {
public:
    Teacher(DataBase *_db);
    ~Teacher();

public:
    QString GetNewWords(bool ruToDeDirection);
    bool CheckResult(bool ruToDeDirection, const QString &answer, QString &correctAnswer);

    void UpdateDBAfterStudy();

private:
    DataBase *db;
    std::vector<StudyEntry> entries;
};

#endif // TEACHER_H
