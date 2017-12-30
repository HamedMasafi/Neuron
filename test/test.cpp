//#define NEURONPEER_H
//#include "../src/syntax/syntax.h"
#include "test.h"

N_CLASS_IMPL(Test)

N_PROPERTY_IMPL(Test, int, t, t, setT, tChanged)

N_REMOTE_METHOD_IMPL(Test, void, setTime)
 
