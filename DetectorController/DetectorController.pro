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
    ../Metadata/Metadata.cpp \
    ../Settings/Settings.cpp \
    ../Mission/Mission.cpp

HEADERS += \
    DetectorController.h \
    ../Metadata/Metadata.h \
    ../Settings/Settings.h \
    ../Mission/Mission.h

INCLUDEPATH += $$PWD/../Settings \
    $$PWD/../Metadata \
    $$PWD/../Mission
