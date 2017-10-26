#ifndef TEACHER_H
#define TEACHER_H

#include "database.h"

#include <vector>

class Teacher {
public:
    Teacher(DataBase *_db);
    ~Teacher();

public:
    const QString* GetWord() const;
    bool CheckResult(const QString &answer, QString &correctAnswer);

    bool RuToDe() const {return ruToDe; }
    void SetRuToDe(bool val) { ruToDe = val; }

private:
    DataBase *db;

    bool ruToDe;

    size_t currentPairIndex;
    bool learnedByFirstTime;

    std::vector<StudyEntry> entries;
};

#endif // TEACHER_H
