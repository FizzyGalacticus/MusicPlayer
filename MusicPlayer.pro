#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T18:35:59
#
#-------------------------------------------------

QT       += core gui multimedia
QT       += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    actions.cpp \
    componentactions.cpp \
    menuactions.cpp \
    menus.cpp \
    setup.cpp \
    sqlite.cpp \
    getLyrics.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
