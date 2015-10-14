#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T10:46:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RawData
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    RawData.cpp \
    ../Settings/Settings.cpp

HEADERS += \
    RawData.h \
    ../Settings/Settings.h

INCLUDEPATH += $$PWD/../Settings
