/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <settings_global.h>

#ifndef DWIDGET_NAMESPACE

#define DWIDGET_NAMESPACE Widget
#define DTK_WIDGET_NAMESPACE DTK_NAMESPACE::Widget

#   define DWIDGET_BEGIN_NAMESPACE namespace DTK_NAMESPACE { namespace DWIDGET_NAMESPACE {
#   define DWIDGET_END_NAMESPACE }}
#   define DWIDGET_USE_NAMESPACE using namespace DTK_WIDGET_NAMESPACE;

#endif

#if defined(STATIC_LIB)
    #  define SETTINGVIEWSHARED_EXPORT
#else
    #if defined(LIBDTKWIDGET_LIBRARY)
    #  define SETTINGVIEWSHARED_EXPORT Q_DECL_EXPORT
    #else
    #  define SETTINGVIEWSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif
