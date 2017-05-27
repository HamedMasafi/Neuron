#define METHOD_DECL_P_SIGNAL_VOID(ret, name, count, sep, ...) \
    void name##Signal(__NAMEVALUE(count, __VA_ARGS__));

#define METHOD_DECL_P_SIGNAL_NONVOID(ret, name, count, sep, ...) \
    void name##Signal(__NAMEVALUE(count, __VA_ARGS__) sep ret &returnValue);
