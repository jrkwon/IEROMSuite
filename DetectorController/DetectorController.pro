#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T16:13:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = DetectorController
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    DetectorController.cpp \
    ../RawData/RawData.cpp \
    ../Settings/Settings.cpp

HEADERS += \
    DetectorController.h \
    ../RawData/RawData.h \
    ../Settings/Settings.h

INCLUDEPATH += $$PWD/../Settings \
    $$PWD/../RawData
