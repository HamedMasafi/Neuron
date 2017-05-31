//void foo(int n, const QObject *obj, const QMetaMethod *callbackMethod);
#ifndef NO_META_METHOD
#   define METHOD_DECL_P_META_METHOD(ret, name, count, sep, ...) \
        void name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod);

#   define METHOD_IMPL_P_META_METHOD_VOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod)); \
            addCall(__call_id, call);  \
        }   \
    }

#   define METHOD_IMPL_P_META_METHOD_NONVOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NoronRemoteCall<ret> *call = new NoronRemoteCall<ret>(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod)); \
            addCall(__call_id, call);  \
        }   \
    }

#else
#   define METHOD_DECL_P_META_METHOD(...)
#   define METHOD_IMPL_P_META_METHOD_VOID(...)
#   define METHOD_IMPL_P_META_METHOD_NONVOID(...)
#endif
