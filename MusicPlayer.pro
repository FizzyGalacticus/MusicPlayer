#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T14:06:54
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basePlayer.cpp \
    controlpanel.cpp \
    mediaplayertabwidget.cpp

HEADERS  += mainwindow.h \
    basePlayer.h \
    controlpanel.h \
    mediaplayertabwidget.h

FORMS    += mainwindow.ui
