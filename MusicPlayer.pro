#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T14:06:54
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app

SOURCES += main.cpp\
	mainwindow.cpp \
    basePlayer.cpp \
    controlpanel.cpp \
    mediaplayertabwidget.cpp \
    lyricbox.cpp \
    progressbar.cpp \
    videowidget.cpp \
    mediadatabase.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    basePlayer.h \
    controlpanel.h \
    mediaplayertabwidget.h \
    lyricbox.h \
    progressbar.h \
    videowidget.h \
    mediadatabase.h \
    user.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

win32 {
QMAKE_CXXFLAGS += -std=c++11
}

unix {
QMAKE_CXXFLAGS += -std=c++0x
}

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android