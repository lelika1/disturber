#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T20:29:05
#
#-------------------------------------------------

QT       += core gui sql
QTPLUGIN += qsqlite

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LangLearn
TEMPLATE = app

SOURCES += main.cpp\
        startwindow.cpp \
    addwordswindow.cpp \
    database.cpp \
    dictionarywindow.cpp \
    studywindow.cpp \
    superedit.cpp \
    teacher.cpp \
    settings.cpp \
    resultswindow.cpp

HEADERS  += startwindow.h \
    addwordswindow.h \
    database.h \
    dictionarywindow.h \
    studywindow.h \
    superedit.h \
    teacher.h \
    settings.h \
    resultswindow.h

FORMS    += startwindow.ui \
    addwordswindow.ui \
    dictionarywindow.ui \
    studywindow.ui \
    superedit.ui \
    settings.ui \
    resultswindow.ui
