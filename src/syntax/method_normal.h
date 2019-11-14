#define METHOD_IMPL_P_NORMAL(class, ret, name, count, sep, ...) \
    CALL(ret) *class::name(__NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            CALL(ret) *call = new CALL(ret)();    \
            addCall(__call_id, call);  \
            return call; \
        }   \
        return nullptr; \
    }
