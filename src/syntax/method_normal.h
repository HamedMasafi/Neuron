// void foo(int n);
#ifndef NO_NORMAL
#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...) \
        ret name(__NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_NORMAL_VOID(class, ret, name, count, sep, ...) \
    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NEURON_WRAP_NAMESPACE(RemoteCallBase) *call = new NEURON_WRAP_NAMESPACE(RemoteCallBase)(NEURON_WRAP_NAMESPACE(RemoteCallBase::EventLoop));    \
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
            NEURON_WRAP_NAMESPACE(RemoteCall)<ret> *call = new NEURON_WRAP_NAMESPACE(RemoteCall)<ret>(NEURON_WRAP_NAMESPACE(RemoteCallBase::EventLoop));    \
            addCall(__call_id, call);  \
            call->eventLoop->exec();    \
            removeCall(__call_id); \
            ret val = call->returnData.value<ret>(); \
            return val; \
        }   \
        return ret(); \
    }

#   define METHOD_IMPL_P_NORMAL(class, ret, name, count, sep, ...) \
    NEURON_WRAP_NAMESPACE(Call)<ret> * class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NEURON_WRAP_NAMESPACE(Call)<ret> *call = new NEURON_WRAP_NAMESPACE(Call)<ret>();    \
            addCall(__call_id, call);  \
            return call; \
        }   \
        return nullptr; \
    }

#else
#   define METHOD_DECL_P_NORMAL(...)
#   define METHOD_IMPL_P_NORMAL_VOID(...)
#   define METHOD_IMPL_P_NORMAL_NONVOID(...)
#endif
