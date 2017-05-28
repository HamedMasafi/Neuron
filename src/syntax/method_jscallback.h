//void foo(int n, QJSValue callbackFunction);
#ifndef NO_QML_CALLBACK
#   define METHOD_DECL_P_QML_CALLBACK(ret, name, count, sep, ...) \
        Q_INVOKABLE void name(__NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction);

#   define METHOD_IMPL_P_QML_CALLBACK_VOID(class, ret, name, count, sep, ...) \
        void class::name(__NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction)    \
        {\
            qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
            if(id){ \
                NoronRemoteCallBase *call = new NoronRemoteCallBase(callbackFunction, hub()->qmlEngine(), hub()->jsEngine());   \
                addCall(id, call);  \
            }   \
        }

#   define METHOD_IMPL_P_QML_CALLBACK_NONVOID(class, ret, name, count, sep, ...) \
        void class::name(__NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction)    \
        {  \
            qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
            if(id){ \
                NoronRemoteCall<ret> *call = new NoronRemoteCall<ret>(callbackFunction, hub()->qmlEngine(), hub()->jsEngine());   \
                addCall(id, call);  \
            }   \
        }

#else
#   define METHOD_DECL_P_QML_CALLBACK(...)
#   define METHOD_IMPL_P_QML_CALLBACK_VOID(...)
#   define METHOD_IMPL_P_QML_CALLBACK_NONVOID(...)
#endif
