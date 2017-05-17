/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "settings.h"

#include <QMap>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QThread>
#include <QDebug>

#include "option.h"
#include "group.h"
#include "backend.h"

#include "backend/qsettingbackend.h"

DTK_BEGIN_NAMESPACE

class SettingsPrivate
{
public:
    SettingsPrivate(Settings *parent) : q_ptr(parent) {}

    Backend                     *backend = nullptr;
    QMap <QString, OptionPtr>   options;

    QMap<QString, GroupPtr>     childGroups;
    QList<QString>              childGroupKeys;

    Settings *q_ptr;
    Q_DECLARE_PUBLIC(Settings)
};


Settings::Settings(QObject *parent) :
    QObject(parent), d_ptr(new SettingsPrivate(this))
{
}

Settings::~Settings()
{

}

void Settings::setBackend(Backend *backend)
{
    Q_D(Settings);
    if (nullptr == backend) {
        return;
    }

    if (d->backend != nullptr) {
        qWarning() << "set backend to exist " << d->backend;
    }

    d->backend = backend;
    auto backendWriteThread = new QThread;
    d->backend->moveToThread(backendWriteThread);
    backendWriteThread->start();

    // load form backend
    loadValue();
}

QPointer<Settings> Settings::fromJson(const QByteArray &json)
{
    auto settingsPtr = QPointer<Settings>(new Settings);
    settingsPtr->parseJson(json);
    return settingsPtr;
}

QPointer<Settings> Settings::fromJsonFile(const QString &filepath)
{
    QFile jsonFile(filepath);
    jsonFile.open(QIODevice::ReadOnly);
    auto jsonData = jsonFile.readAll();
    jsonFile.close();

    return Settings::fromJson(jsonData);
}

QStringList Settings::keys() const
{
    Q_D(const Settings);
    return d->options.keys();
}

QPointer<Option> Settings::option(const QString &key) const
{
    Q_D(const Settings);
    return d->options.value(key);
}

QVariant Settings::value(const QString &key) const
{
    Q_D(const Settings);
    auto opt = d->options.value(key);
    if (opt.isNull()) {
        return QVariant();
    }

    return opt->value();
}

QStringList Settings::groupKeys() const
{
    Q_D(const Settings);
    return d->childGroupKeys;
}

QList<QPointer<Group> > Settings::groups() const
{
    Q_D(const Settings);
    return d->childGroups.values();
}

QPointer<Group> Settings::group(const QString &key) const
{
    Q_D(const Settings);
    return d->childGroups.value(key);
}

QList<QPointer<Option> > Settings::options() const
{
    Q_D(const Settings);
    return d->options.values();
}

QVariant Settings::getOption(const QString &key) const
{
    return option(key)->value();
}

void Settings::setOption(const QString &key, const QVariant &value)
{
//    Q_D(Settings);
//    qDebug() << "set" << key << value;
    option(key)->setValue(value);
}

void Settings::sync()
{
    Q_D(Settings);
    d->backend->doSync();
}

void Settings::reset()
{
    Q_D(Settings);

    for (auto option : d->options) {
        if (option->canReset()) {
            setOption(option->key(), option->defaultValue());
        }
    }
    d->backend->sync();
}

void Settings::parseJson(const QByteArray &json)
{
    Q_D(Settings);

    auto jsonDoc = QJsonDocument::fromJson(json);
    auto mainGroups = jsonDoc.object().value("groups");
    for (auto groupJson : mainGroups.toArray()) {
        auto group = Group::fromJson("", groupJson.toObject());
        for (auto option : group->options()) {
//            qDebug() << "add option" << option->key();
            d->options.insert(option->key(), option);
        }
        d->childGroupKeys << group->key();
        d->childGroups.insert(group->key(), group);
    }

    for (auto option :  d->options.values()) {
        d->options.insert(option->key(), option);

        connect(option.data(), &Option::valueChanged,
        this, [ = ](QVariant value) {
            emit d->backend->setOption(option->key(), value);
//            emit d->backend->sync();
            emit valueChanged(option->key(), value);
        });
    }
}

void Settings::loadValue()
{
    Q_D(Settings);

//    qDebug() << d->backend;
    for (auto key : d->backend->keys()) {
        //qDebug() << "load value for key" << key;
        auto value = d->backend->getOption(key);
        auto opt = option(key);
        if (!value.isValid() || opt.isNull()) {
            continue;
        }

        opt->blockSignals(true);
        opt->setValue(value);
        opt->blockSignals(false);
    }
}

DTK_END_NAMESPACE
