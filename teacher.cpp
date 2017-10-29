#include "settings.h"
#include "teacher.h"

#include <ctime>
#include <algorithm>

Configurator &config = Configurator::Instance();

Teacher::Teacher(DataBase *_db)
    : db(_db)
    , ruToDe(true)
    , currentPairIndex(0)
    , learnedByFirstTime(true)
{
    ReadStudyEntries(entries);
}

void Teacher::ReadStudyEntries(std::vector<StudyEntry>& _entries) {
    std::set<int> ids;
    size_t totalWords = config.GetWordsCountPerTraining();
    // We will try to select 2*N words and then select a random subset of N words from it.
    size_t selectWords = 2 * totalWords;
    size_t oldWords = (selectWords * config.GetPercentOfOldWordsPerTraining()) / 100;
    size_t worstKnownWords = selectWords - oldWords;
    db->SelectNOldest(oldWords, ids);
    db->SelectNWorstKnown(worstKnownWords, ids);

    std::vector<int> resultIds(ids.begin(), ids.end());
    std::random_shuffle(resultIds.begin(), resultIds.end());
    if (resultIds.size() > totalWords) {
        resultIds.erase(resultIds.begin() + totalWords, resultIds.end());
    }
    db->SelectByIds(resultIds, _entries);
}

const QString* Teacher::GetWord() const {
    if (currentPairIndex >= entries.size() || currentPairIndex >= config.GetWordsCountPerTraining()) {
        return nullptr;
    }
    const auto &currentPair = entries[currentPairIndex];
    return (ruToDe) ? &currentPair.ruWord : &currentPair.deWord;
}

bool Teacher::CheckResult(const QString &answer, QString &correctAnswer) {
    auto& entry = entries[currentPairIndex];
    correctAnswer = (ruToDe) ? entry.deWord : entry.ruWord;
    bool isCorrect = (answer.toLower() == correctAnswer.toLower());

    if (learnedByFirstTime) {
        if (entry.successRate == 0) {
             entry.successRate = 1;
        }
        entry.successRate *= (1.0 * (config.GetSuccessRate() - 1) / config.GetSuccessRate());
        entry.successRate += (1.0 / config.GetSuccessRate()) * ((isCorrect) ? 1 : 0);
        entry.lastTestDate = std::time(nullptr);
        learnedByFirstTime = isCorrect;
    }

    if (isCorrect) {
        db->UpdateEntry(entry);
        ++currentPairIndex;
        learnedByFirstTime = true;
    }

    return isCorrect;
}
