// void foo(int n);
#ifndef NO_NORMAL
#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...) \
        ret name(__NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_NORMAL_VOID(class, ret, name, count, sep, ...) \
    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NeuronRemoteCallBase *call = new NeuronRemoteCallBase(NeuronRemoteCallBase::EventLoop);    \
            addCall(__call_id, call);  \
            call->eventLoop->exec();    \
            removeCall(__call_id); \
        }   \
    }

#   define METHOD_IMPL_P_NORMAL_NONVOID(class, ret, name, count, sep, ...) \
    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NeuronRemoteCall<ret> *call = new NeuronRemoteCall<ret>(NeuronRemoteCallBase::EventLoop);    \
            addCall(__call_id, call);  \
            call->eventLoop->exec();    \
            removeCall(__call_id); \
            ret val = call->returnData.value<ret>(); \
            return val; \
        }   \
        return ret(); \
    }

#else
#   define METHOD_DECL_P_NORMAL(...)
#   define METHOD_IMPL_P_NORMAL_VOID(...)
#   define METHOD_IMPL_P_NORMAL_NONVOID(...)
#endif
