﻿#include "teacher.h"

const int KWordsPerStudy = 2;
const int KSuccessRate = 3;

Teacher::Teacher(DataBase *_db)
    : db(_db)
    , currentPairIndex(0)
    , learnedByFirstTime(true)
    , successWordsInStudy(0)
{}

Teacher::~Teacher() {}

bool Teacher::InitStudy() {
    db->SelectAllEntries(entries);
    std::sort(begin(entries), end(entries),
              [](StudyEntry first, StudyEntry second){return first.successRate < second.successRate;});
    currentPairIndex = 0;
    successWordsInStudy = 0;
    return entries.size() != 0;
}

bool Teacher::GetNewPair(bool ruToDeDirection, QString& originalWord) {
    if (currentPairIndex == entries.size() || successWordsInStudy == KWordsPerStudy) {
        return false;
    }
    originalWord = (ruToDeDirection) ? entries[currentPairIndex].ruWord : entries[currentPairIndex].deWord;
    return true;
}

bool Teacher::CheckResult(bool ruToDeDirection, const QString &answer, QString &correctAnswer) {
    correctAnswer = (ruToDeDirection) ? entries[currentPairIndex].deWord : entries[currentPairIndex].ruWord;
    bool isCorrect = (answer == correctAnswer);

    if (learnedByFirstTime) {
        if (entries[currentPairIndex].successRate == 0) {
             entries[currentPairIndex].successRate = 1;
        }
        entries[currentPairIndex].successRate *= (1.0 * (KSuccessRate - 1) / KSuccessRate);
        entries[currentPairIndex].successRate += (1.0 / KSuccessRate) * ((isCorrect) ? 1 : 0);
        entries[currentPairIndex].isDirty = true;
        learnedByFirstTime = isCorrect;
    }

    if (isCorrect) {
        ++successWordsInStudy;
        ++currentPairIndex;
        learnedByFirstTime = true;
    }

    return isCorrect;
}

void Teacher::UpdateDBAfterStudy() {
    db->UpdateEntries(entries);
}
