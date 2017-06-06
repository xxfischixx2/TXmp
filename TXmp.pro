#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T20:02:10
#
#-------------------------------------------------

QT       += core gui multimedia \
            testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TXmp
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           settings.cpp \
    faudioplayer.cpp

HEADERS  += mainwindow.h \
            settings.h \
    faudioplayer.h

FORMS    += mainwindow.ui \
            settings.ui

RESOURCES += Resources.qrc
