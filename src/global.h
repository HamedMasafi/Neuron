/**************************************************************************
**
** This file is part of .
** https://github.com/HamedMasafi/
**
**  is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with .  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NEURONGLOBAL_H
#define NEURONGLOBAL_H

#include <QtCore/QtGlobal>

//#define NEURON_NAMESPACE 

#define NEURON_VERSION 0x000100
#define NEURON_VERSION_STR "0.1.0"

#define NEURON_NAMESPACE Neuron

#ifdef NEURON_NAMESPACE
#   define NEURON_NAMESPACE_STR QT_STRINGIFY(NEURON_NAMESPACE)
#   define NEURON_BEGIN_NAMESPACE     namespace NEURON_NAMESPACE {
#   define NEURON_END_NAMESPACE       }
#   define NEURON_WRAP_NAMESPACE(x)   NEURON_NAMESPACE::x
#else
#   define NEURON_NAMESPACE_STR
#   define NEURON_BEGIN_NAMESPACE
#   define NEURON_END_NAMESPACE
#   define NEURON_WRAP_NAMESPACE(x)   x
#endif

#ifdef KAJ_LOGGER_LIB
#   include "logger.h"
#   include "objectprofiller.h"
#else
#   define K_TRACE_DEBUG
#   define K_REG_OBJECT(x)
#   define K_TRACE(...)
#   define K_INFORMATION(...)
#   define K_WARNING(...)
#   define K_ERROR(...)
#endif

#ifdef NEURON_COMPILE_STATIC
#   define NEURON_EXPORT
#else
#   define NEURON_EXPORT Q_DECL_EXPORT
#endif

#ifdef QDATASTREAM_H
#   define NEURON_OPERATORS_FOR_ENUM(ENUM) \
        QDataStream& operator>> (QDataStream& s, ENUM& type) \
        { \
            qint32 n; \
            s >> n; \
            type = static_cast<ENUM>(n); \
            return s; \
        }; \
        QDataStream& operator<< (QDataStream& s, const ENUM& type) \
        { \
            return (s << (qint32)type); \
        };
#else
#   define NEURON_OPERATORS_FOR_ENUM(ENUM) \
        QT_DO_PRAGMA("GCC error QDataStream not included")

#endif

//#define NEURON_SHARED_POINTER
#ifdef NEURON_SHARED_POINTER
template <class T>
using PointerList = QList<QSharedPointer<T>>;

template <class T>
using PointerSet = QSet<QSharedPointer<T>>;

template <typename T>
using Pointer = QSharedPointer<T>;

template<class T>
inline Pointer<T> createPointer() {
    return QSharedPointer<T>(new T);
}

template<class T>
inline Pointer<T> createPointer(QObject *parent) {
    return QSharedPointer<T>(new T(parent));
}

#else
//template <typename T>
//using PointerList = QList<T*>;

//template <typename T>
//using PointerSet = QSet<T*>;

//template <typename T>
//using Pointer = T*;

//template<class T>
//inline Pointer<T> createPointer() {
//    return new T;
//}

//template<class T>
//inline Pointer<T> createPointer(QObject *parent) {
//    return new T(parent);
//}

#endif

#endif // NEURONGLOBAL_H

