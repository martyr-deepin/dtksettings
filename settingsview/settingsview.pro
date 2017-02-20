#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T19:16:02
#
#-------------------------------------------------

include($$PWD/../common/lib.pri)

QT       += widgets

TARGET = dtksettingsview
TEMPLATE = lib

DEFINES += SETTINGVIEW_LIBRARY

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
    widget/navigationdelegate.cpp \
    widgetfactory.cpp \
    widget/contenttitle.cpp \
    widget/shortcutedit.cpp \
    widget/buttongroup.cpp \
    content.cpp \
    navigation.cpp \
    widget/combobox.cpp

HEADERS +=\
    widget/navigationdelegate.h \
    widgetfactory.h \
    widget/contenttitle.h \
    widget/shortcutedit.h \
    widget/buttongroup.h \
    settingsview_global.h \
    content.h \
    navigation.h \
    widget/combobox.h

includes.path = $${DTK_INCLUDEPATH}/DSettingsView
includes.files += $${PWD}/*.h
includes.files += $${PWD}/widget/*.h

QMAKE_PKGCONFIG_NAME = DTK_SETTINGS_VIEW
QMAKE_PKGCONFIG_DESCRIPTION = Deepin Tool Kit Settings UI Header Files
QMAKE_PKGCONFIG_INCDIR = $$includes.path

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../settings/release/ -ldtksettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../settings/debug/ -ldtksettings
else:unix: LIBS += -L$$OUT_PWD/../settings/ -ldtksettings

INCLUDEPATH += $$PWD/../settings
DEPENDPATH += $$PWD/../settings

RESOURCES += \
    widget/theme.qrc

DISTFILES += \
    widget/theme/light/ButtonGroup.theme
