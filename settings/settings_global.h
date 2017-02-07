/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <QtCore/qglobal.h>

#ifndef DTK_NAMESPACE
    #define DTK_NAMESPACE Dtk
#endif

#if !defined(DTK_NAMESPACE)
#   define DTK_BEGIN_NAMESPACE
#   define DTK_END_NAMESPACE
#   define DTK_USE_NAMESPACE
#else
#   define DTK_BEGIN_NAMESPACE namespace DTK_NAMESPACE {
#   define DTK_END_NAMESPACE }
#   define DTK_USE_NAMESPACE using namespace DTK_NAMESPACE;
#endif

#if defined(STATIC_LIB)
    #  define SETTINGSSHARED_EXPORT
#else
    #if defined(SETTINGS_LIBRARY)
    #  define SETTINGSSHARED_EXPORT Q_DECL_EXPORT
    #else
    #  define SETTINGSSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif

