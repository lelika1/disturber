#include "settings.h"
#include "studysession.h"

#include <ctime>
#include <algorithm>

Configurator &config = Configurator::Instance();

StudySession::StudySession(DataBase *_db, bool ruToDeDirection, size_t wordsCount, const QStringList &topicsList)
    : db(_db)
    , ruToDe(ruToDeDirection)
    , wordsPerSession(wordsCount)
    , wordsTopicsList(topicsList)
    , currentPairIndex(0)
    , learnedByFirstTime(true)
{
    ReadStudyEntries(entries);
}

void StudySession::ReadStudyEntries(std::vector<StudyEntry>& entries_) {
    std::set<int> ids;
    size_t totalWords = wordsPerSession;
    // We will try to select 2*N words and then select a random subset of N words from it.
    size_t selectWords = 2 * totalWords;
    size_t oldWords = (selectWords * config.GetPercentOfOldWordsPerSession()) / 100;
    size_t worstKnownWords = selectWords - oldWords;
    db->SelectNOldest(wordsTopicsList, oldWords, ids);
    db->SelectNWorstKnown(wordsTopicsList, worstKnownWords, ids);

    std::vector<int> resultIds(ids.begin(), ids.end());
    std::random_shuffle(resultIds.begin(), resultIds.end());
    if (resultIds.size() > totalWords) {
        resultIds.erase(resultIds.begin() + totalWords, resultIds.end());
    }
    std::vector<DBEntry> tmp;
    db->SelectByIds(resultIds, tmp);
    for (auto& e : tmp) {
        entries_.emplace_back(std::move(e));
    }
}

const QString* StudySession::GetWord() const {
    if (currentPairIndex >= entries.size() || currentPairIndex >= wordsPerSession) {
        return nullptr;
    }
    const auto &currentPair = entries[currentPairIndex];
    return (ruToDe) ? &currentPair.ruWord : &currentPair.deWord;
}

bool StudySession::SubmitAnswer(const QString &answer, QString &correctAnswer) {
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
