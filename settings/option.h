/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <QVariant>
#include <QObject>
#include <QPointer>

#include "settings_global.h"

DTK_BEGIN_NAMESPACE

class Group;
class OptionPrivate;
class Option : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit Option(QObject *parent = 0);
    ~Option();

    QPointer<Group> parentGroup() const;
    void setParentGroup(QPointer<Group> parentGroup);

    QString key() const;
    QString name() const;
    bool canReset() const;
    QVariant defaultValue() const;
    QVariant value() const;
    QVariant data(const QString &dataType) const;

    QString viewType() const;
    bool isHidden() const;

    static QPointer<Option> fromJson(const QString &prefixKey, const QJsonObject &group);
signals:
    void valueChanged(QVariant value);
    void dataChanged(const QString &dataType, QVariant value);

public slots:
    void setValue(QVariant value);
    void setData(const QString &dataType, QVariant value);

private:
    void parseJson(const QString &prefixKey, const QJsonObject &option);

    QScopedPointer<OptionPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), Option)
};

typedef QPointer<Option> OptionPtr;

DTK_END_NAMESPACE
