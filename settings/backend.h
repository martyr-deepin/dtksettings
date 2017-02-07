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

#include "settings_global.h"

DTK_BEGIN_NAMESPACE

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = 0): QObject(parent) {}
    virtual ~Backend() {}

    virtual void sync() = 0;

    virtual QStringList keys() const = 0;
    virtual QVariant getOption(const QString &key) const = 0;
    virtual void setOption(const QString &key, const QVariant &value) = 0;

signals:
    void optionChanged(const QString &key, const QVariant &value);
};

DTK_END_NAMESPACE
