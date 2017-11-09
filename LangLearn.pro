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
    settings.cpp \
    resultswindow.cpp \
    setupstudywindow.cpp \
    studysession.cpp

HEADERS  += startwindow.h \
    addwordswindow.h \
    database.h \
    dictionarywindow.h \
    studywindow.h \
    superedit.h \
    settings.h \
    resultswindow.h \
    setupstudywindow.h \
    studysession.h

FORMS    += startwindow.ui \
    addwordswindow.ui \
    dictionarywindow.ui \
    studywindow.ui \
    superedit.ui \
    settings.ui \
    resultswindow.ui \
    setupstudywindow.ui
