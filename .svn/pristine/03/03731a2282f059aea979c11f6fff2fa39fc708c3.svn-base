#ifndef RPCGLOBAL_H
#define RPCGLOBAL_H

#include <QtGlobal>


/*
 * Multi thread server. If flowinf macro is defiened server run every peer in a seprated thread. Disable
 * flowing line to force sever to run all of peers in main thread
 */
//#define RPC_THREADED

/*
 * Token for message validate. This token prevent external request injection. Comment flowing line
 * for disabling this feauture.
 * Note: this token must be same on client and server app
 */
//#define RPC_TOKEN       "saj2l3kj09vcxu09)(#()*XJkhksad="


#define TOOJ_VERSION 0x000100
#define TOOJ_VERSION_STR "0.1.0"

#ifdef TOOJ_COMPILE_STATIC
#   define TOOJ_EXPORT
#else
#   define TOOJ_EXPORT Q_DECL_EXPORT
#endif // BUILD_CORE

#endif // RPCGLOBAL_H

