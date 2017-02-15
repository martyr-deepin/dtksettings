/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "navigation.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QListView>
#include <QStandardItemModel>

#include <group.h>
#include <settings.h>

#include "widget/navigationdelegate.h"

DWIDGET_BEGIN_NAMESPACE

class NavigationPrivate
{
public:
    NavigationPrivate(Navigation *parent) : q_ptr(parent) {}

    QListView           *navbar         = nullptr;
    QStandardItemModel  *navbarModel    = nullptr;

    Navigation *q_ptr;
    Q_DECLARE_PUBLIC(Navigation)
};

Navigation::Navigation(QWidget *parent) :
    QFrame(parent), d_ptr(new NavigationPrivate(this))
{
    Q_D(Navigation);

    setObjectName("Navigation");
//    setStyleSheet("#Navigation{border: none; border-right: 1px solid rgba(0,0,0,0.1);}");

    setContentsMargins(0, 0, 0, 0);
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    d->navbar = new QListView(this);
    d->navbar->setObjectName("NavigationBar");
//    d->navbar->setStyleSheet("#NavigationBar{border: none;}");
    d->navbar->setFixedWidth(160);
    d->navbar->setContentsMargins(0, 0, 0, 0);

    d->navbarModel = new QStandardItemModel;

    d->navbar->setModel(d->navbarModel);

    d->navbar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    d->navbar->setItemDelegate(new NavigationDelegate);

    layout->addWidget(d->navbar);

    connect(d->navbar, &QListView::clicked,
    this, [ = ](const QModelIndex & index) {
        qDebug() << index.data(NavigationDelegate::NavKeyRole);
        auto key = index.data(NavigationDelegate::NavKeyRole).toString();
        if (!key.isEmpty()) {
            emit selectedGroup(index.data(NavigationDelegate::NavKeyRole).toString());
        }
    });

    setFixedWidth(d->navbar->width() + 1);
}

Navigation::~Navigation()
{
}

void Navigation::onSelectGroup(const QString &key)
{
    Q_D(Navigation);
    for (int i = 0; i < d->navbarModel->rowCount(); ++i) {
        auto index = d->navbarModel->index(i, 0);
        if (index.data(NavigationDelegate::NavKeyRole).toString() == key) {
            d->navbar->setCurrentIndex(index);
            return;
        }
    }
}

void Navigation::updateSettings(QPointer<Dtk::Settings> settings)
{
    Q_D(Navigation);

    bool first = true;
    for (auto groupKey : settings->groupKeys()) {
        if (!first) {
            auto item = new QStandardItem;
            item->setData("", Qt::DisplayRole);
            item->setData(NavigationDelegate::Split, NavigationDelegate::NavLevelRole);
            d->navbarModel->appendRow(item);
        }
        first = false;

        auto item = new QStandardItem;
        auto trName = QObject::tr(settings->group(groupKey)->name().toStdString().c_str());
        qDebug() << settings->group(groupKey)->name() << trName;
        item->setData(trName, Qt::DisplayRole);
        item->setData(NavigationDelegate::Level1, NavigationDelegate::NavLevelRole);
        item->setData(groupKey, NavigationDelegate::NavKeyRole);
        d->navbarModel->appendRow(item);

        for (auto subgroup : settings->group(groupKey)->childGroups()) {
            if (subgroup->name().isEmpty()) {
                continue;
            }

            auto item = new QStandardItem;
            auto trName = QObject::tr(subgroup->name().toStdString().c_str());
            qDebug() << subgroup->name() << trName;
            item->setData(trName, Qt::DisplayRole);
            item->setData(NavigationDelegate::Level2, NavigationDelegate::NavLevelRole);
            item->setData(subgroup->key(), NavigationDelegate::NavKeyRole);
            d->navbarModel->appendRow(item);
        }
    }

    d->navbar->setCurrentIndex(d->navbarModel->index(0, 0));
}

DWIDGET_END_NAMESPACE
