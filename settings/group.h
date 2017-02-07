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
#include <QPointer>

#include "option.h"

#include "settings_global.h"

DTK_BEGIN_NAMESPACE

class GroupPrivate;
class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(QObject *parent = 0);
    ~Group();

    QPointer<Group> parentGroup() const;
    void setParentGroup(QPointer<Group> parentGroup);

    QString key() const;
    QString name() const;

    QList<QPointer<Group> > childGroups() const;
    QList<QPointer<Option> > childOptions() const;
    QList<QPointer<Option> > options() const;

    static QPointer<Group> fromJson(const QString &prefixKey, const QJsonObject &group);
signals:

public slots:

private:
    void parseJson(const QString &prefixKey, const QJsonObject &group);

    QScopedPointer<GroupPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), Group)
};

typedef QPointer<Group> GroupPtr;

DTK_END_NAMESPACE
