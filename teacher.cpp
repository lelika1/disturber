#include "settings.h"
#include "teacher.h"

#include <ctime>

Configurator &config = Configurator::Instance();

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
    if (currentPairIndex == entries.size() || successWordsInStudy == config.GetWordsCountPerTraining()) {
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
        entries[currentPairIndex].successRate *= (1.0 * (config.GetSuccessRate() - 1) / config.GetSuccessRate());
        entries[currentPairIndex].successRate += (1.0 / config.GetSuccessRate()) * ((isCorrect) ? 1 : 0);
        entries[currentPairIndex].lastTestDate = std::time(nullptr);
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
    entries.clear();
}
