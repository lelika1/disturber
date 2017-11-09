#include "settings.h"
#include "studysession.h"

#include <algorithm>

Configurator &config = Configurator::Instance();

StudySession::StudySession(DataBase *_db, bool ruToDeDirection, size_t wordsCount, const QStringList &topicsList)
    : db(_db)
    , ruToDe(ruToDeDirection)
    , wordsPerSession(wordsCount)
    , wordsTopicsList(topicsList)
    , currentPairIndex(0)
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

const QString* StudySession::GetWord() {
    if (currentPairIndex >= entries.size() || currentPairIndex >= wordsPerSession) {
        return nullptr;
    }
    StudyEntry &entry = entries[currentPairIndex];
    if (entry.startTime == 0) {
        entry.startTime = std::time(nullptr);
    }
    return (ruToDe) ? &entry.ruWord : &entry.deWord;
}

bool StudySession::SubmitAnswer(const QString &answer, QString &correctAnswer) {
    StudyEntry& entry = entries[currentPairIndex];
    entry.attempts++;
    correctAnswer = (ruToDe) ? entry.deWord : entry.ruWord;
    bool isCorrect = (answer.toLower() == correctAnswer.toLower());

    if (entry.attempts == 1) {
        entry.firstAnswer = answer;
        entry.firstSubmissionTime = std::time(nullptr);
        if (entry.successRate == 0) {
             entry.successRate = 1;
        }
        entry.successRate *= (1.0 * (config.GetSuccessRate() - 1) / config.GetSuccessRate());
        entry.successRate += (1.0 / config.GetSuccessRate()) * ((isCorrect) ? 1 : 0);
        entry.lastTestDate = std::time(nullptr);
    }

    if (isCorrect) {
        db->UpdateEntry(entry);
        ++currentPairIndex;
    }

    return isCorrect;
}

int StudySession::rowCount(const QModelIndex &/*parent*/) const  {
    return entries.size();
}

int StudySession::columnCount(const QModelIndex &/*parent*/) const {
    return 5;
}

QVariant StudySession::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }
    switch (section) {
    case 0: return "Russian";
    case 1: return "Deutsch";
    case 2: return "Your first answer";
    case 3: return "Attempts";
    case 4: return "First Answer Latency";
    default:return QVariant();
    }
}

QVariant StudySession::data(const QModelIndex &index, int role) const {
    return entries.at(index.row()).data(index.column(), role);
}

bool StudySession::setData(const QModelIndex &index, const QVariant & value, int role) {
    return entries.at(index.row()).setData(index.column(), value, role);
}

Qt::ItemFlags StudySession::flags(const QModelIndex &index) const {
    switch (index.column()) {
    case 0:
        return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    case 1:
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    default:
        return Qt::ItemIsEnabled;
    }
}

QVariant StudyEntry::data(int col, int role) const {
    if (role == Qt::CheckStateRole) {
        if (col == 0) {
            return checked ? Qt::Checked : Qt::Unchecked;
        }
        return QVariant();
    }
    if (role == Qt::BackgroundRole) {
        return (attempts > 1) ? QBrush(Qt::red) : QVariant();
    }
    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0: return ruWord;
        case 1: return deWord;
        case 2: return firstAnswer;
        case 3: return QString::number(attempts);
        case 4: return QString::number(firstSubmissionTime - startTime).append("s");
        default: return QVariant();
        }
    }
    if (role == Qt::EditRole) {
        switch (col) {
        case 0: return ruWord;
        case 1: return deWord;
        default: return QVariant();
        }
    }
    return QVariant();
}

bool StudyEntry::setData(int col, const QVariant &value, int role) {
    switch (col) {
    case 0: {
        if (role == Qt::CheckStateRole) {
            checked = (value == Qt::Checked);
            return true;
        }
        if (role == Qt::EditRole) {
            ruWord = value.toString();
            return true;
        }
        return false;
    }
    case 1:{
        if (role != Qt::EditRole) return false;
        deWord = value.toString();
        return true;
    }
    default:
        return false;
    }
}
