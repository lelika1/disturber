#include "teacher.h"

Teacher::Teacher(DataBase *_db)
    : db(_db)
{}

Teacher::~Teacher() {}

QString Teacher::GetNewWords(bool ruToDeDirection) {
    return (ruToDeDirection) ? "русский" : "deutsch";
}

bool Teacher::CheckResult(bool ruToDeDirection, const QString &answer, QString &correctAnswer) {
    correctAnswer = (ruToDeDirection)? "deutsch" : "русский";
    return (answer == correctAnswer);
}

void Teacher::UpdateDBAfterStudy() {

}
