//void foo(int n, const QObject *obj, char *callbackSlot);
#ifndef NO_SLOT_CALLBACK
#   define METHOD_DECL_P_SLOT_CALLBACK(ret, name, count, sep, ...) \
        Q_INVOKABLE void name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot);

#   define METHOD_IMPL_P_SLOT_CALLBACK_VOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(const_cast<QObject *>(obj), callbackSlot);  \
            addCall(__call_id, call);  \
        }   \
    }

#   define METHOD_IMPL_P_SLOT_CALLBACK_NONVOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NoronRemoteCall<ret> *call = new NoronRemoteCall<ret>(const_cast<QObject *>(obj), callbackSlot);  \
            addCall(__call_id, call);  \
        }   \
    }

#else
#   define METHOD_DECL_P_SLOT_CALLBACK(...)
#   define METHOD_DECL_P_SLOT_CALLBACK_NONVOID(...)
#   define METHOD_IMPL_P_SLOT_CALLBACK(...)
#   define METHOD_IMPL_P_SLOT_CALLBACK_NONVOID(...)
#endif
