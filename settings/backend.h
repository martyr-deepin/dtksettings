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
    explicit Backend(QObject *parent = 0): QObject(parent)
    {
        connect(this, &Backend::sync, this, &Backend::doSync, Qt::QueuedConnection);
        connect(this, &Backend::setOption, this, &Backend::doSetOption, Qt::QueuedConnection);
    }
    virtual ~Backend() {}

    virtual QStringList keys() const = 0;
    virtual QVariant getOption(const QString &key) const = 0;

    virtual void doSync() = 0;

protected:
    virtual void doSetOption(const QString &key, const QVariant &value) = 0;

signals:
    void sync();
    void setOption(const QString &key, const QVariant &value);
    void optionChanged(const QString &key, const QVariant &value);
};

DTK_END_NAMESPACE
