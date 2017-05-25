/**************************************************************************
**
** This file is part of Noron.
** https://github.com/HamedMasafi/Noron
**
** Noron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Noron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Noron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NORONGLOBAL_H
#define NORONGLOBAL_H

#include <QtCore/QtGlobal>

//#define NORON_NAMESPACE Noron

#define NORON_VERSION 0x000100
#define NORON_VERSION_STR "0.1.0"

#ifdef NORON_NAMESPACE
#   define NORON_BEGIN_NAMESPACE     namespace NORON_NAMESPACE {
#   define NORON_END_NAMESPACE       }
#else
#   define NORON_BEGIN_NAMESPACE
#   define NORON_END_NAMESPACE
#endif

#ifdef KAJ_LOGGER_LIB
#   include "logger.h"
#   include "objectprofiller.h"
#else
#   define K_REG_OBJECT(x)
#   define K_TRACE(...)
#   define K_INFORMATION(...)
#   define K_WARNING(...)
#   define K_ERROR(...)
#endif

#ifdef NORON_COMPILE_STATIC
#   define NORON_EXPORT
#else
#   define NORON_EXPORT Q_DECL_EXPORT
#endif

#endif // NORONGLOBAL_H

