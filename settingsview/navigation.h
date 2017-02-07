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
#include <QFrame>

#include "settingsview_global.h"

DTK_BEGIN_NAMESPACE
class Settings;
DTK_END_NAMESPACE

DWIDGET_BEGIN_NAMESPACE

class NavigationPrivate;
class SETTINGVIEWSHARED_EXPORT Navigation : public QFrame
{
    Q_OBJECT
public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();

signals:
    void selectedGroup(const QString &key);

public slots:
    void onSelectGroup(const QString &key);
    void updateSettings(QPointer<Dtk::Settings> settings);

private:
    QScopedPointer<NavigationPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), Navigation)
};

DWIDGET_END_NAMESPACE
