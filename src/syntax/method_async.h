// void fooAsync(int n);
#ifndef NO_NORMAL_ASYNC
#   define METHOD_DECL_P_ASYNC(ret, name, count, sep, ...) \
        void name##Async(__NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_ASYNC(class, ret, name, count, sep, ...) \
    void class::name##Async(__NAMEVALUE(count, __VA_ARGS__))   \
    {   \
        invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
    }

#else
#   define METHOD_DECL_P_ASYNC(...)
#   define METHOD_IMPL_P_ASYNC(...)
#endif
