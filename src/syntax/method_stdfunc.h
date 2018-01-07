//int callNumber(int number, std::function<void(int)> callbackFunction);
#ifndef NO_STD_FUNC
#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...) \
        void name(__NAMEVALUE(count, __VA_ARGS__) sep std::function<void(ret)> callbackFunction);

#   define METHOD_IMPL_P_STD_FUNC_VOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep std::function<void(ret)> callbackFunction) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NEURON_WRAP_NAMESPACE(NeuronRemoteCallBase) *call = new NEURON_WRAP_NAMESPACE(NeuronRemoteCallBase)(callbackFunction);  \
            addCall(__call_id, call);  \
        }   \
    }

#   define METHOD_IMPL_P_STD_FUNC_NONVOID(class, ret, name, count, sep, ...) \
    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep std::function<void(ret)> callbackFunction) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
        if (__call_id) { \
            NEURON_WRAP_NAMESPACE(NeuronRemoteCall)<ret> *call = new NEURON_WRAP_NAMESPACE(NeuronRemoteCall)<ret>(callbackFunction);  \
            addCall(__call_id, call);  \
        }   \
    }

#else
#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...)
#   define METHOD_IMPL_P_STD_FUNC_VOID(class, ret, name, count, sep, ...)
#   define METHOD_IMPL_P_STD_FUNC_NONVOID(class, ret, name, count, sep, ...)
#endif

