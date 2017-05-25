#ifndef NO_SLOT
#ifdef NORONSHAREDOBJECT_H
#   define METHOD_DECL_P_SLOT(ret, name, count, sep, ...) \
        virtual ret name##Slot(NoronPeer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_SLOT_VOID(class, ret, name, count, sep, ...) \
        void class::name##Slot(NoronPeer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__)) \
        {   \
            Q_EMIT name##Signal(senderPeer sep __PARAMNAME(count, __VA_ARGS__)); \
        }
#   define METHOD_IMPL_P_SLOT_NONVOID(class, ret, name, count, sep, ...) \
        ret class::name##Slot(NoronPeer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__)) \
        {   \
            ret r; \
            Q_EMIT name##Signal(senderPeer sep __PARAMNAME(count, __VA_ARGS__) , r); \
            return r; \
        }
#else
#   define METHOD_DECL_P_SLOT(ret, name, count, sep, ...) \
        virtual ret name##Slot(__NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_SLOT_VOID(class, ret, name, count, sep, ...) \
        void class::name##Slot(__NAMEVALUE(count, __VA_ARGS__)) \
        {   \
            Q_EMIT name##Signal(__PARAMNAME(count, __VA_ARGS__)); \
        }

#   define METHOD_IMPL_P_SLOT_NONVOID(class, ret, name, count, sep, ...) \
        ret class::name##Slot(__NAMEVALUE(count, __VA_ARGS__)) \
        {   \
            ret r; \
            Q_EMIT name##Signal(__PARAMNAME(count, __VA_ARGS__) sep r); \
            return r; \
        }

#endif

#else
#   define METHOD_DECL_P_SLOT(...)
#   define METHOD_IMPL_P_SLOT_VOID(...)
#   define METHOD_IMPL_P_SLOT_NONVOID(...)
#endif
