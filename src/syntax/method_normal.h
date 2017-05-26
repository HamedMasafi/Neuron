// void foo(int n);
#ifndef NO_NORMAL
#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...) \
        ret name(__NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_NORMAL_VOID(class, ret, name, count, sep, ...) \
    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(NoronRemoteCallBase::EventLoop);    \
            addCall(id, call);  \
            call->eventLoop->exec();    \
            removeCall(id); \
        }   \
    }

#   define METHOD_IMPL_P_NORMAL_NONVOID(class, ret, name, count, sep, ...) \
    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if(id){ \
            NoronRemoteCall<ret> *call = new NoronRemoteCall<ret>(NoronRemoteCallBase::EventLoop);    \
            addCall(id, call);  \
            call->eventLoop->exec();    \
            removeCall(id); \
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
