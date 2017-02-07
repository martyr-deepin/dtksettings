#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T10:52:30
#
#-------------------------------------------------

include($$PWD/../common/lib.pri)

QT       -= gui

TARGET = dtksettings
TEMPLATE = lib

DEFINES += SETTINGS_LIBRARY
CONFIG += c++11 create_pc create_prl no_install_prl

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    settings.cpp \
    option.cpp \
    group.cpp \
    backend/qsettingbackend.cpp

HEADERS +=\
    settings_global.h \
    settings.h \
    option.h \
    backend.h \
    group.h \
    backend/qsettingbackend.h


includes.path = $${DTK_INCLUDEPATH}/DSettings
includes.files += $${PWD}/*.h
includes.files += $${PWD}/backend/*.h

QMAKE_PKGCONFIG_NAME = DTK_SETTINGS
QMAKE_PKGCONFIG_DESCRIPTION = Deepin Tool Kit Settings Header Files
QMAKE_PKGCONFIG_INCDIR = $$includes.path
