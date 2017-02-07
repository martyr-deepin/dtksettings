/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "group.h"

#include <QMap>
#include <QJsonObject>
#include <QJsonArray>

DTK_BEGIN_NAMESPACE

class GroupPrivate
{
public:
    GroupPrivate(Group *parent) : q_ptr(parent) {}

    QString key;
    QString name;

    QMap<QString, OptionPtr>    options;

    QPointer<Group>             parent;
    QMap<QString, OptionPtr>    childOptions;
    QList<QString>              childOptionKeys;

    QMap<QString, GroupPtr>     childGroups;
    QList<QString>              childGroupKeys;

    void parseJson(const QString &prefixKey, const QJsonObject &group);

    Group *q_ptr;
    Q_DECLARE_PUBLIC(Group)
};

Group::Group(QObject *parent) :
    QObject(parent), d_ptr(new GroupPrivate(this))
{

}

Group::~Group()
{

}

QPointer<Group> Group::parentGroup() const
{
    Q_D(const Group);
    return d->parent;
}

void Group::setParentGroup(QPointer<Group> parentGroup)
{
    Q_D(Group);
    d->parent = parentGroup;
}

QString Group::key() const
{
    Q_D(const Group);
    return d->key;
}

QString Group::name() const
{
    Q_D(const Group);
    return d->name;
}

QList<QPointer<Group> > Group::childGroups() const
{
    Q_D(const Group);
    QList<QPointer<Group> > grouplist;
    for (auto groupKey : d->childGroupKeys) {
        grouplist << d->childGroups.value(groupKey);
    }
    return grouplist;
}

QList<QPointer<Option> > Group::childOptions() const
{
    Q_D(const Group);
    QList<QPointer<Option> > optionlist;
    for (auto optionKey : d->childOptionKeys) {
        optionlist << d->childOptions.value(optionKey);
    }
    return optionlist;
}

QList<QPointer<Option> > Group::options() const
{
    Q_D(const Group);
    return d->options.values();
}

QPointer<Group> Group::fromJson(const QString &prefixKey, const QJsonObject &group)
{
    auto groupPtr = QPointer<Group>(new Group);
    groupPtr->parseJson(prefixKey, group);
    return groupPtr;
}

void Group::parseJson(const QString &prefixKey, const QJsonObject &group)
{
    Q_D(Group);
    d->parseJson(prefixKey, group);
}

void GroupPrivate::parseJson(const QString &prefixKey, const QJsonObject &group)
{
    Q_Q(Group);
    key = group.value("key").toString();
    Q_ASSERT(!key.isEmpty());
    key = prefixKey.isEmpty() ? key : prefixKey + "." + key;
    name = group.value("name").toString();

    for (auto optionJson :  group.value("options").toArray()) {
        auto optionObject = optionJson.toObject();
        auto option = Option::fromJson(key, optionObject);
        options.insert(option->key(), option);
        childOptions.insert(option->key(), option);
        childOptionKeys << option->key();
    }

    auto subGroups = group.value("groups").toArray();
    for (auto subGroup : subGroups) {
        auto child = Group::fromJson(key, subGroup.toObject());
        child->setParentGroup(q);
        childGroups.insert(child->key(), child);
        childGroupKeys << child->key();

        for (auto option : child->options()) {
            options.insert(option->key(), option);
        }
    }

}

DTK_END_NAMESPACE
