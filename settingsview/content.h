/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <QScopedPointer>
#include <QPointer>
#include <QFrame>

#include "settingsview_global.h"

DTK_BEGIN_NAMESPACE
class Settings;
DTK_END_NAMESPACE

DWIDGET_BEGIN_NAMESPACE

class WidgetFactory;
class ContentPrivate;
class SETTINGVIEWSHARED_EXPORT Content : public QFrame
{
    Q_OBJECT
public:
    explicit Content(QWidget *parent = 0);
    ~Content();

    WidgetFactory* widgetFactory();
signals:
    void scrollToGroup(const QString &key);

public slots:
    void onScrollToGroup(const QString &key);
    void updateSettings(QPointer<Dtk::Settings> settings);

private:
    QScopedPointer<ContentPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), Content)
};

DWIDGET_END_NAMESPACE
