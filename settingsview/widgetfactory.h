/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <QObject>
#include <QScopedPointer>

#include "settingsview_global.h"

DTK_BEGIN_NAMESPACE
class Option;
DTK_END_NAMESPACE

DWIDGET_BEGIN_NAMESPACE

typedef QWidget *(*WidgetCreateHandle)(QObject *);

class WidgetFactoryPrivate;
class SETTINGVIEWSHARED_EXPORT WidgetFactory : public QObject
{
    Q_OBJECT
public:
    explicit WidgetFactory(QObject *parent = 0);
    ~WidgetFactory();

    void registerWidget(const QString &viewType, WidgetCreateHandle handle);
    QWidget *createWidget(QPointer<Dtk::Option> option);
signals:

public slots:
    static QWidget *createTwoColumHandle(Dtk::Option *option, QWidget *rightWidget);

private:
    QScopedPointer<WidgetFactoryPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), WidgetFactory)
};

DWIDGET_END_NAMESPACE
