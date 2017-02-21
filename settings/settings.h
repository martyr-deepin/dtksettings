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
#include <QScopedPointer>

#include "settings_global.h"

DTK_BEGIN_NAMESPACE

class Backend;
class Option;
class Group;
class SettingsPrivate;
class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    void setBackend(Backend *backend = nullptr);

    static QPointer<Settings> fromJson(const QByteArray &json);
    static QPointer<Settings> fromJsonFile(const QString &filepath);

    QStringList keys() const;
    QList<QPointer<Option>> options() const;
    QPointer<Option> option(const QString &key) const;
    QVariant value(const QString &key) const;

    QStringList groupKeys() const;
    QList<QPointer<Group>> groups() const;
    QPointer<Group> group(const QString &key) const;

    QVariant getOption(const QString &key) const;

signals:
    void valueChanged(const QString& key, const QVariant& value);

public slots:
    //!
    //! \brief sync
    //! WARNING: sync will block
    void sync() ;

    void setOption(const QString &key, const QVariant &value);
    void reset() ;

private:
    void parseJson(const QByteArray &json);
    void loadValue();

    QScopedPointer<SettingsPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), Settings)
};

DTK_END_NAMESPACE
