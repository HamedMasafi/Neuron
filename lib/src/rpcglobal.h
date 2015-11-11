#ifndef RPCGLOBAL_H
#define RPCGLOBAL_H

#include <QtGlobal>

#define QT_NAMESPACE rpc

#define TOOJ_VERSION 0x000100
#define TOOJ_VERSION_STR "0.1.0"

#ifdef TOOJ_COMPILE_STATIC
#   define TOOJ_EXPORT
#else
#   define TOOJ_EXPORT Q_DECL_EXPORT
#endif

#endif // RPCGLOBAL_H

