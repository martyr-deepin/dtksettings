#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T19:53:21
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = settingsdialog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        settingsdialog.cpp \
    translation.cpp

HEADERS  += settingsdialog.h

RESOURCES += \
    config.qrc


TRANSLATIONS += $$PWD/translations/$${TARGET}.ts \
                $$PWD/translations/$${TARGET}_zh_CN.ts

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../settingsview/release/ -ldtksettingsview
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../settingsview/debug/ -ldtksettingsview
else:unix: LIBS += -L$$OUT_PWD/../settingsview/ -ldtksettingsview

INCLUDEPATH += $$PWD/../settingsview
DEPENDPATH += $$PWD/../settingsview

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../settings/release/ -ldtksettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../settings/debug/ -ldtksettings
else:unix: LIBS += -L$$OUT_PWD/../settings/ -ldtksettings

INCLUDEPATH += $$PWD/../settings
DEPENDPATH += $$PWD/../settings
