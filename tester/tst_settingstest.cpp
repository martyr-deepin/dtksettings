/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include <QString>
#include <QtTest>
#include <QTemporaryFile>

#include "option.h"
#include "settings.h"
#include "backend/qsettingbackend.h"

class SettingsTest : public QObject
{
    Q_OBJECT

public:
    SettingsTest();

private Q_SLOTS:
    void testParseJsonFile();
};

SettingsTest::SettingsTest()
{
}

void SettingsTest::testParseJsonFile()
{
    QVERIFY2(true, "Failure");

    auto settings = Dtk::Settings::fromJsonFile(":/data/settins.json");

    QTemporaryFile tmpFile;
    tmpFile.open();
    auto backend = new Dtk::QSettingBackend(tmpFile.fileName());
    settings->setBackend(backend);

    QCOMPARE(settings.isNull(), false);

    auto autoPlayOpt = settings->option("base.play.auto_play");
    QCOMPARE(autoPlayOpt.isNull(), false);
    QCOMPARE(autoPlayOpt->defaultValue().toBool(), false);

    autoPlayOpt->setValue(true);
    settings->sync();

    settings->reset();
    settings->sync();
}

QTEST_APPLESS_MAIN(SettingsTest)

#include "tst_settingstest.moc"
