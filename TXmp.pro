#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T20:02:10
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TXmp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    fmediaplayer.cpp

HEADERS  += mainwindow.h \
    settings.h \
    fmediaplayer.h

FORMS    += mainwindow.ui \
    settings.ui

DISTFILES +=

RESOURCES += \
    Resources.qrc

LIBS += "/usr/lib/x86_64-linux-gnu/libpulse-mainloop-glib.so.0" -lpulse-mainloop-glib \
        "/usr/lib/x86_64-linux-gnu/libpulse.so.0" -lpulse\
        "/lib/x86_64-linux-gnu/libglib-2.0.so.0" -lglib-2.0
