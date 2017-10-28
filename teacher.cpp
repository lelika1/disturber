#include "settings.h"
#include "teacher.h"

#include <ctime>

Configurator &config = Configurator::Instance();

Teacher::Teacher(DataBase *_db)
    : db(_db)
    , ruToDe(true)
    , currentPairIndex(0)
    , learnedByFirstTime(true)
{
    db->SelectAllEntries(entries);
    std::sort(begin(entries), end(entries),
              [](const StudyEntry &first, const StudyEntry &second){return first.successRate < second.successRate;});
}

Teacher::~Teacher() {}

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
    bool isCorrect = (answer == correctAnswer);

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
