/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "settingsdialog.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString translatePath = ":/translations/settingsdialog_zh_CN.qm";
    auto translator = new QTranslator(&a);
    translator->load(translatePath);
    a.installTranslator(translator);

    SettingsDialog w;
    w.setFixedSize(680, 540);
    w.show();
    w.adjustSize();
    return a.exec();
}
