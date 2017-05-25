#ifndef CLIENT
#define CLIENT

#define NO_NORMAL
#define NO_NORMAL_ASYNC
#define NO_META_METHOD
#define NO_QML_CALLBACK
#define NO_SLOT_CALLBACK
#define NO_STD_FUNC
#define NO_SLOT
#define NORONPEER_H

#define QObject int
#define NoronPeer
#include "../src/syntax/syntax.h"

class Test : public NoronPeer
{
    N_CLASS_DECLARE(Test)

    N_PROPERTY_DECL(int, t, t, setT, tChanged)
    N_REMOTE_METHOD_DECL(void, setTime)
};
#endif // CLIENT
 
