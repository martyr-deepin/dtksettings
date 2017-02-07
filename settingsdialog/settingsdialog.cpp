/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "settingsdialog.h"

#include <QHBoxLayout>
#include <QFontDatabase>
#include <QTextCodec>
#include <QTemporaryFile>

#include "option.h"
#include "settings.h"
#include "backend/qsettingbackend.h"

#include "navigation.h"
#include "content.h"

DWIDGET_USE_NAMESPACE

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto settings = Dtk::Settings::fromJsonFile(":/data/settins.json");
    QTemporaryFile tmpFile;
    tmpFile.open();
    auto backend = new Dtk::QSettingBackend(tmpFile.fileName());
    settings->setBackend(backend);

    auto nav = new Navigation;
    nav->updateSettings(settings);

    auto content = new Content;
    content->updateSettings(settings);

    layout->addWidget(nav);
    layout->addWidget(content);

    connect(nav, &Navigation::selectedGroup, content, &Content::onScrollToGroup);
    connect(content, &Content::scrollToGroup, nav, &Navigation::onSelectGroup);

    QFontDatabase fontDatabase;
    auto fontFamliy = settings->option("base.font.family");
    fontFamliy->setData("items", fontDatabase.families());
    fontFamliy->setValue(0);

    QStringList codings;
    for (auto coding: QTextCodec::availableCodecs())
        codings << coding;

    auto encoding = settings->option("advance.encoding.encoding");
    encoding->setData("items", codings);
    encoding->setValue(0);
}

SettingsDialog::~SettingsDialog()
{

}
