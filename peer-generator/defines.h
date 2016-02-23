#ifndef DEFINES_H
#define DEFINES_H

#include <QtGlobal>

#ifdef Q_OS_WIN
#   define LB "\r\n"
#endif
#ifdef Q_OS_UNIX
#   define LB "\n"
#endif
#ifdef Q_OS_MACOSX
#   define LB "\r"
#endif

#endif // DEFINES_H
