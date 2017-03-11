/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "option.h"

#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

DTK_BEGIN_NAMESPACE

class OptionPrivate
{
public:
    OptionPrivate(Option *parent) : q_ptr(parent) {}

    void parseJson(const QString &prefixKey, const QJsonObject &option);

    QPointer<Group>             parent;

    QString     key;
    QString     name;
    QString     viewType;
    QVariant    defalutValue;
    QVariant    value;
    QVariantMap datas;
    bool        canReset;
    bool        hidden;

    Option *q_ptr;
    Q_DECLARE_PUBLIC(Option)
};

Option::Option(QObject *parent) :
    QObject(parent), d_ptr(new OptionPrivate(this))
{

}

Option::~Option()
{

}

QPointer<Group> Option::parentGroup() const
{
    Q_D(const Option);
    return d->parent;
}

void Option::setParentGroup(QPointer<Group> parentGroup)
{
    Q_D(Option);
    d->parent = parentGroup;
}

QString Option::key() const
{
    Q_D(const Option);
    return d->key;
}

QString Option::name() const
{
    Q_D(const Option);
    return d->name;
}

bool Option::canReset() const
{
    Q_D(const Option);
    return d->canReset;
}

QVariant Option::defaultValue() const
{
    Q_D(const Option);
    return d->defalutValue;
}

QVariant Option::value() const
{
    Q_D(const Option);
    return d->value;
}

QVariant Option::data(const QString &dataType) const
{
    Q_D(const Option);
    return d->datas.value(dataType);
}

QString Option::viewType() const
{
    Q_D(const Option);
    return d->viewType;
}

bool Option::isHidden() const
{
    Q_D(const Option);
    return d->hidden;
}

QPointer<Option> Option::fromJson(const QString &prefixKey, const QJsonObject &group)
{
    auto optionPtr = QPointer<Option>(new Option);
    optionPtr->parseJson(prefixKey, group);
    return optionPtr;
}

void Option::setValue(QVariant value)
{
    Q_D(Option);

    if (d->value == value) {
        return;
    }

    d->value = value;
    emit valueChanged(value);
}

void Option::setData(const QString &dataType, QVariant value)
{
    Q_D(Option);

    if (d->datas.value(dataType) == value) {
        return;
    }

    d->datas.insert(dataType, value);

    emit dataChanged(dataType, value);
}

void Option::parseJson(const QString &prefixKey, const QJsonObject &option)
{
    Q_D(Option);
    d->parseJson(prefixKey, option);
}

void OptionPrivate::parseJson(const QString &prefixKey, const QJsonObject &option)
{
//    Q_Q(Option);
    key = option.value("key").toString();
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!prefixKey.isEmpty());
    key = prefixKey + "." + key;
    name = option.value("name").toString();

    canReset = !option.contains("reset") ? true : option.value("reset").toBool();
    defalutValue = option.value("default").toVariant();
    hidden = !option.contains("hide") ? false : option.value("hide").toBool();
    viewType = option.value("type").toString();
    value = defalutValue;

    QStringList revserdKeys;
    revserdKeys << "key" << "name" << "reset"
                << "default" << "hide" << "type";

    auto allKeys = option.keys();
    for (auto key : revserdKeys) {
        allKeys.removeAll(key);
    }

    for (auto key : allKeys) {
        auto value = option.value(key);
        if (value.isArray()) {
            QStringList stringlist;
            for (auto va: value.toArray()) {
                stringlist << QString("%1").arg(va.toString());
            }
            datas.insert(key, stringlist);
        } else {
            datas.insert(key, value);
        }
    }
}

DTK_END_NAMESPACE


