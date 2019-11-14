#define METHOD_DECL_P_SLOT(ret, name, count, sep, ...) \
        virtual ret name##Slot(__NAMEVALUE(count, __VA_ARGS__));

#define METHOD_IMPL_P_SLOT_VOID(class, ret, name, count, sep, ...) \
        void class::name##Slot(__NAMEVALUE(count, __VA_ARGS__))

#define METHOD_IMPL_P_SLOT_NONVOID(class, ret, name, count, sep, ...) \
        ret class::name##Slot(__NAMEVALUE(count, __VA_ARGS__))
