#ifndef STUDYENTRY_H
#define STUDYENTRY_H

#include "database.h"
#include <chrono>

struct StudyEntry: public DBEntry {
    explicit StudyEntry(DBEntry e) : DBEntry(std::move(e)) {}

    std::chrono::milliseconds first_submission_latency;
    size_t attempts;
    QString first_answer;
};

#endif // STUDYENTRY_H
