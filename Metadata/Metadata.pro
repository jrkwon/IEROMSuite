#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T10:46:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Metadata
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../Settings/Settings.cpp \
    Metadata.cpp

HEADERS += \
    ../Settings/Settings.h \
    Metadata.h

INCLUDEPATH += $$PWD/../Settings
