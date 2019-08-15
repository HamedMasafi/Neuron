//#ifndef SYNTAX_H
//#define SYNTAX_H

//#define __NAMEVALUE2(...)
//#define __NAMEVALUE4(a, b)                                                    a b
//#define __NAMEVALUE6(a, b, c, d)                                              __NAMEVALUE4(a, b), c d
//#define __NAMEVALUE8(a, b, c, d, e, f)                                        __NAMEVALUE6(a, b, c, d), e f
//#define __NAMEVALUE10(a, b, c, d, e, f, g, h)                                 __NAMEVALUE8(a, b, c, d, e, f, g, h), g h
//#define __NAMEVALUE12(a, b, c, d, e, f, g, h, i, j)                           __NAMEVALUE10(a, b, c, d, e, f, g, h, g, h) i j
//#define __NAMEVALUE14(a, b, c, d, e, f, g, h, i, j, k, l)                     __NAMEVALUE12(a, b, c, d, e, f, g, h, g, h, i, j) k l
//#define __NAMEVALUE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __NAMEVALUE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m n
//#define __NAMEVALUE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __NAMEVALUE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o p

//#define __NAMEVALUE1(...)
//#define __NAMEVALUE3(a, b)                                                    a b
//#define __NAMEVALUE5(a, b, c, d)                                              __NAMEVALUE4(a, b), c d
//#define __NAMEVALUE7(a, b, c, d, e, f)                                        __NAMEVALUE6(a, b, c, d), e f
//#define __NAMEVALUE9(a, b, c, d, e, f, g, h)                                  __NAMEVALUE8(a, b, c, d, e, f, g, h), g h
//#define __NAMEVALUE11(a, b, c, d, e, f, g, h, i, j)                           __NAMEVALUE10(a, b, c, d, e, f, g, h, g, h) i j
//#define __NAMEVALUE13(a, b, c, d, e, f, g, h, i, j, k, l)                     __NAMEVALUE12(a, b, c, d, e, f, g, h, g, h, i, j) k l
//#define __NAMEVALUE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __NAMEVALUE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m n
//#define __NAMEVALUE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __NAMEVALUE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o p


//#define __PARAMNAME2(...)
//#define __PARAMNAME4(a, b)                                                    b
//#define __PARAMNAME6(a, b, c, d)                                              __PARAMNAME4(a, b), d
//#define __PARAMNAME8(a, b, c, d, e, f)                                        __PARAMNAME6(a, b, c, d), f
//#define __PARAMNAME10(a, b, c, d, e, f, g, h)                                 __PARAMNAME8(a, b, c, d, e, f, g, h), h
//#define __PARAMNAME12(a, b, c, d, e, f, g, h, i, j)                           __PARAMNAME10(a, b, c, d, e, f, g, h, g, h) j
//#define __PARAMNAME14(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMNAME12(a, b, c, d, e, f, g, h, g, h, i, j) l
//#define __PARAMNAME16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMNAME14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) n
//#define __PARAMNAME18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMNAME16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) p

//#define __PARAMNAME1(...)
//#define __PARAMNAME3(a, b)                                                    b
//#define __PARAMNAME5(a, b, c, d)                                              __PARAMNAME4(a, b), d
//#define __PARAMNAME7(a, b, c, d, e, f)                                        __PARAMNAME6(a, b, c, d), f
//#define __PARAMNAME9(a, b, c, d, e, f, g, h)                                  __PARAMNAME8(a, b, c, d, e, f, g, h), h
//#define __PARAMNAME11(a, b, c, d, e, f, g, h, i, j)                           __PARAMNAME10(a, b, c, d, e, f, g, h, g, h) j
//#define __PARAMNAME13(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMNAME12(a, b, c, d, e, f, g, h, g, h, i, j) l
//#define __PARAMNAME15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMNAME14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) n
//#define __PARAMNAME17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMNAME16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) p

//#define __PARAMTYPE2(...)
//#define __PARAMTYPE4(a, b)                                                    a
//#define __PARAMTYPE6(a, b, c, d)                                              __PARAMTYPE4(a, b), c
//#define __PARAMTYPE8(a, b, c, d, e, f)                                        __PARAMTYPE6(a, b, c, d), e
//#define __PARAMTYPE10(a, b, c, d, e, f, g, h)                                 __PARAMTYPE8(a, b, c, d, e, f, g, h), g
//#define __PARAMTYPE12(a, b, c, d, e, f, g, h, i, j)                           __PARAMTYPE10(a, b, c, d, e, f, g, h, g, h) i
//#define __PARAMTYPE14(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMTYPE12(a, b, c, d, e, f, g, h, g, h, i, j) k
//#define __PARAMTYPE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMTYPE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m
//#define __PARAMTYPE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMTYPE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o

//#define __PARAMTYPE1(...)
//#define __PARAMTYPE3(a, b)                                                    a
//#define __PARAMTYPE5(a, b, c, d)                                              __PARAMTYPE4(a, b), c
//#define __PARAMTYPE7(a, b, c, d, e, f)                                        __PARAMTYPE6(a, b, c, d), e
//#define __PARAMTYPE9(a, b, c, d, e, f, g, h)                                  __PARAMTYPE8(a, b, c, d, e, f, g, h), g
//#define __PARAMTYPE11(a, b, c, d, e, f, g, h, i, j)                           __PARAMTYPE10(a, b, c, d, e, f, g, h, g, h) i
//#define __PARAMTYPE13(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMTYPE12(a, b, c, d, e, f, g, h, g, h, i, j) k
//#define __PARAMTYPE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMTYPE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m
//#define __PARAMTYPE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMTYPE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o

//#define __SEP1
//#define __SEP2
//#define __SEP3 				,
//#define __SEP4 				,
//#define __SEP5 				,
//#define __SEP6 				,
//#define __SEP7 				,
//#define __SEP8 				,
//#define __SEP9 				,
//#define __SEP10 				,
//#define __SEP11 				,
//#define __SEP12 				,
//#define __SEP13 				,
//#define __SEP14 				,
//#define __SEP15 				,
//#define __SEP16 				,

//#define __RETTYPE0(r)           void
//#define __RETTYPE1(r)           void
//#define __RETTYPE2(r)           r
//#define __RETTYPE3(r)           void
//#define __RETTYPE4(r)           r
//#define __RETTYPE5(r)           void
//#define __RETTYPE6(r)           r
//#define __RETTYPE7(r)           void
//#define __RETTYPE8(r)           r
//#define __RETTYPE9(r)           void
//#define __RETTYPE10(r)          r
//#define __RETTYPE11(r)          void
//#define __RETTYPE12(r)          r
//#define __RETTYPE13(r)          void
//#define __RETTYPE14(r)          r
//#define __RETTYPE15(r)          void
//#define __RETTYPE16(r)          r

//#define __PARAMS0()          //r
//#define __PARAMS1(r)          //r, __VA_ARGS__
//#define __PARAMS2(...)          __VA_ARGS__
//#define __PARAMS3(r, ...)          r, __VA_ARGS__
//#define __PARAMS4(r, ...)          __VA_ARGS__
//#define __PARAMS5(r, ...)          r, __VA_ARGS__
//#define __PARAMS6(r, ...)          __VA_ARGS__
//#define __PARAMS7(r, ...)          r, __VA_ARGS__
//#define __PARAMS8(r, ...)          __VA_ARGS__
//#define __PARAMS9(r, ...)          r, __VA_ARGS__
//#define __PARAMS10(r, ...)          __VA_ARGS__
//#define __PARAMS11(r, ...)          r, __VA_ARGS__
//#define __PARAMS12(r, ...)          __VA_ARGS__
//#define __PARAMS13(r, ...)          r, __VA_ARGS__
//#define __PARAMS14(r, ...)          __VA_ARGS__
//#define __PARAMS15(r, ...)          r, __VA_ARGS__
//#define __PARAMS16(r, ...)          __VA_ARGS__

////#define __FUNCNAME0(r)          r
//#define __FUNCNAME1(r)              r
//#define __FUNCNAME2(r,n)          n
//#define __FUNCNAME3(r, name, ...)          r
//#define __FUNCNAME4(r, name, ...)          name
//#define __FUNCNAME5(r, name, ...)          r
//#define __FUNCNAME6(r, name, ...)          name
//#define __FUNCNAME7(r, name, ...)          r
//#define __FUNCNAME8(r, name, ...)          name
//#define __FUNCNAME9(r, name, ...)          r
//#define __FUNCNAME10(r, name, ...)          name
//#define __FUNCNAME11(r, name, ...)          r
//#define __FUNCNAME12(r, name, ...)          name
//#define __FUNCNAME13(r, name)          r
//#define __FUNCNAME14(r, name)          name
//#define __FUNCNAME15(r, name)          r
//#define __FUNCNAME16(r, name)          name

//#define VA_NARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...)     N
//#define VA_NARGS(...)                                           VA_NARGS_IMPL(__VA_ARGS__,9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
//#define VA_ODDEVEN(...)                                         VA_NARGS_IMPL(__VA_ARGS__,odd, even, odd, even, odd, even, odd, even, odd, even)

//#define PP_NARG(...) \
//         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
//#define PP_NARG_(...) \
//         PP_ARG_N(__VA_ARGS__)
//#define PP_ARG_N( \
//          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
//         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
//         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
//         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
//         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
//         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
//         _61,_62,_63,N,...) N
//#define PP_RSEQ_N() \
//         63,62,61,60,                   \
//         59,58,57,56,55,54,53,52,51,50, \
//         49,48,47,46,45,44,43,42,41,40, \
//         39,38,37,36,35,34,33,32,31,30, \
//         29,28,27,26,25,24,23,22,21,20, \
//         19,18,17,16,15,14,13,12,11,10, \
//         9,8,7,6,5,4,3,2,1,0

//#define __PARAMS_odd(n, ...)              n, __VA_ARGS__
//#define __PARAMS_even(n, ...)             __VA_ARGS__

////TODO :

//#define FIRST_ARG_(N, ...) N
//#define FIRST_ARG(args) FIRST_ARG_ args

//#define __FUNCNAME_odd(r, ...)             r
//#define __FUNCNAME_even(r, n, ...)         n

//#define __RETTYPE_odd(...)                   void
//#define __RETTYPE_even(r, ...)                  r

//#define __NAMEVALUE(count, ...)             __NAMEVALUE ## count(__VA_ARGS__)
//#define __PARAMTYPE(count, ...)             __PARAMTYPE ## count(__VA_ARGS__)
//#define __PARAMNAME(count, ...)             __PARAMNAME ## count(__VA_ARGS__)
//#define __SEP(count)                        __SEP ## count

//#define __PARAMS(count, name, ...)          __PARAMS ## count(__VA_ARGS__)
//#define __FUNCNAME(count, ...)              __FUNCNAME ## count(__VA_ARGS__)
//#define __RETTYPE(oddeven, ...)             __RETTYPE_ ## oddeven(__VA_ARGS__)

//// define methods
//#ifndef QT_LIB_QML
//#   define NO_QML_CALLBACK
//#endif
//#if __cplusplus < 201103L
//#    define NO_STD_FUNC
//#endif

//// void foo(int n);
//#ifndef NO_NORMAL
//#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...) \
//        ret name(__NAMEVALUE(count, __VA_ARGS__));

//#   define METHOD_IMPL_P_NORMAL_odd(class, ret, name, count, sep, ...) \
//    void class::name(__NAMEVALUE(count, __VA_ARGS__)) \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);    \
//            addCall(id, call);  \
//            call->eventLoop->exec();    \
//            removeCall(id); \
//            delete call;    \
//        }   \
//    }

//#   define METHOD_IMPL_P_NORMAL_even(class, ret, name, count, sep, ...) \
//    ret class::name(__NAMEVALUE(count, __VA_ARGS__)) \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            RemoteCall<ret> *call = new RemoteCall<ret>(RemoteCallBase::EventLoop);    \
//            addCall(id, call);  \
//            call->eventLoop->exec();    \
//            removeCall(id); \
//            ret val = call->returnData.value<ret>(); \
//            delete call;    \
//            return val; \
//        }   \
//        return ret(); \
//    }

//#else
//#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_NORMAL_even(class, ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_NORMAL_odd(class, ret, name, count, sep, ...)
//#endif

//// void fooAsync(int n);
//#ifndef NO_NORMAL_ASYNC
//#   define METHOD_DECL_P_ASYNC(ret, name, count, sep, ...) \
//        void name##Async(__NAMEVALUE(count, __VA_ARGS__));

//#   define METHOD_IMPL_P_ASYNC(class, ret, name, count, sep, ...) \
//    void class::name##Async(__NAMEVALUE(count, __VA_ARGS__))   \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);    \
//            addCall(id, call);  \
//        }   \
//    }
//#else
//#   define METHOD_DECL_P_ASYNC(ret, name, count, sep, ...)
//#endif

////void foo(int n, const QObject *obj, const QMetaMethod *callbackMethod);
//#ifndef NO_META_METHOD
//#   define METHOD_DECL_P_META_METHOD(ret, name, count, sep, ...) \
//        void name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod);

//#   define METHOD_IMPL_P_META_METHOD(class, ret, name, count, sep, ...) \
//    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod) \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            QObject *target = const_cast<QObject *>(obj);   \
//            RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod)); \
//            addCall(id, call);  \
//        }   \
//    }
//#else
//#   define METHOD_DECL_P_META_METHOD(ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_META_METHOD(class, ret, name, count, sep, ...)
//#endif

////void foo(int n, QJSValue callbackFunction);
//#ifndef NO_QML_CALLBACK
//#   define METHOD_DECL_P_QML_CALLBACK(ret, name, count, sep, ...) \
//        void name(__NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction);

//#   define METHOD_IMPL_P_QML_CALLBACK(class, ret, name, count, sep, ...) \
//    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction)    \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            RemoteCallBase *call = new RemoteCallBase(callbackFunction, hub()->qmlEngine(), hub()->jsEngine());   \
//            addCall(id, call);  \
//        }   \
//    }
//#else
//#   define METHOD_DECL_P_QML_CALLBACK(ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_QML_CALLBACK(class, ret, name, count, sep, ...)
//#endif

////void foo(int n, const QObject *obj, char *callbackSlot);
//#ifndef NO_SLOT_CALLBACK
//#   define METHOD_DECL_P_SLOT_CALLBACK(ret, name, count, sep, ...) \
//        Q_INVOKABLE void name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot);

//#   define METHOD_IMPL_P_SLOT_CALLBACK(class, ret, name, count, sep, ...) \
//    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot) \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);  \
//            addCall(id, call);  \
//        }   \
//    }
//#else
//#   define METHOD_DECL_P_SLOT_CALLBACK(ret, name, count, sep, ...)
//#endif

////int callNumber(int number, std::function<int(void)> callbackFunction);
//#ifndef NO_STD_FUNC
//#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...) \
//        void name(__NAMEVALUE(count, __VA_ARGS__) sep std::function<ret(__PARAMTYPE(count, __VA_ARGS__))> callbackFunction);

//#   define METHOD_IMPL_P_STD_FUNC(class, ret, name, count, sep, ...) \
//    void class::name(__NAMEVALUE(count, __VA_ARGS__) sep std::function<ret(__PARAMTYPE(count, __VA_ARGS__))> callbackFunction) \
//    {   \
//        qlonglong id = invokeOnPeer(#name "Slot" sep __PARAMNAME(count, __VA_ARGS__));  \
//        if(id){ \
//            /*RemoteCallBase *call = new RemoteCallBase(callbackFunction);  \
//            addCall(id, call);*/  \
//        }   \
//    }
//#else
//#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_STD_FUNC(class, ret, name, count, sep, ...)
//#endif


//#ifndef NO_SLOT
//#ifdef NEURONSHAREDOBJECT_H
//#   define METHOD_DECL_P_SLOT(ret, name, count, sep, ...) \
//        virtual void name##Slot(Peer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__));

//#   define METHOD_IMPL_P_SLOT(class, ret, name, count, sep, ...) \
//    void class::name##Slot(Peer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__)) \
//    {   \
//        Q_EMIT name##Signal(senderPeer sep __PARAMNAME(count, __VA_ARGS__)); \
//    }
//#else
//#   define METHOD_DECL_P_SLOT(ret, name, count, sep, ...) \
//        virtual void name##Slot(__NAMEVALUE(count, __VA_ARGS__));

//#   define METHOD_IMPL_P_SLOT(class, ret, name, count, sep, ...) \
//    void class::name##Slot(__NAMEVALUE(count, __VA_ARGS__)) \
//    {   \
//        Q_EMIT name##Signal(__PARAMNAME(count, __VA_ARGS__)); \
//    }
//#endif


//#else
//#   define METHOD_DECL_P_SLOT(ret, name, count, sep, ...)
//#   define METHOD_IMPL_P_SLOT(class, ret, name, count, sep, ...)
//#endif



////signals:
////  void callNumberSignal(int number);
//#ifdef NEURONSHAREDOBJECT_H
//#   define METHOD_DECL_P_SIGNAL(ret, name, count, sep, ...) \
//        void name##Signal(Peer *senderPeer sep __NAMEVALUE(count, __VA_ARGS__));

//#else
//#   define METHOD_DECL_P_SIGNAL(ret, name, count, sep, ...) \
//        void name##Signal(__NAMEVALUE(count, __VA_ARGS__));
//#endif


//#define REMOTE_METHOD_DECL_P(ret, name, count, oe, ...) \
//    ret name(__NAMEVALUE(count, __VA_ARGS__)); \
//    ret name ## Callback(__NAMEVALUE(count, __VA_ARGS__));

//#define __REMOTE_METHOD_DECL_P3(ret, name, count, oe, ...) \
//    public Q_SLOTS: \
//    METHOD_DECL_P_NORMAL        (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_ASYNC         (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_META_METHOD   (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_QML_CALLBACK  (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_SLOT_CALLBACK (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_STD_FUNC      (ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_DECL_P_SLOT          (ret, name, count, __SEP(count), __VA_ARGS__) \
//    Q_SIGNALS: \
//    METHOD_DECL_P_SIGNAL        (ret, name, count, __SEP(count), __VA_ARGS__)

//#define __REMOTE_METHOD_IMPL_P3(class, ret, name, count, oe, ...) \
//    METHOD_IMPL_P_NORMAL_##oe   (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_ASYNC         (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_META_METHOD   (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_QML_CALLBACK  (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_SLOT_CALLBACK (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_STD_FUNC      (class, ret, name, count, __SEP(count), __VA_ARGS__) \
//    METHOD_IMPL_P_SLOT          (class, ret, name, count, __SEP(count), __VA_ARGS__)

//#define __REMOTE_METHOD_DECL_P2(count, oe, ...) \
//    __REMOTE_METHOD_DECL_P3(       __RETTYPE(oe, __VA_ARGS__), __FUNCNAME(count, __VA_ARGS__), count, oe, __PARAMS(count, __VA_ARGS__))

//#define __REMOTE_METHOD_IMPL_P2(class, count, oe, ...) \
//    __REMOTE_METHOD_IMPL_P3(class, __RETTYPE(oe, __VA_ARGS__), __FUNCNAME(count, __VA_ARGS__), count, oe, __PARAMS(count, __VA_ARGS__))

////User macros
//#define N_REMOTE_METHOD_DECL(...) \
//    __REMOTE_METHOD_DECL_P2(       PP_NARG(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)

//#define N_REMOTE_METHOD_IMPL(class, ...) \
//    __REMOTE_METHOD_IMPL_P2(class, PP_NARG(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)


////Property
//#define N_PROPERTY_DECL(type, name, read, write, notify) \
//    Q_PROPERTY(type name READ read WRITE write NOTIFY notify USER true) \
//    type m_##name;\
//    public: type name(); \
//    public Q_SLOTS: void write(type name); \
//    Q_SIGNALS: void notify(type name);

//#define N_PROPERTY_IMPL(class, type, name, read, write, notify)    \
//    type class::name(){    \
//        return m_##name;    \
//    } \
//    void class::write(type name){ \
//        m_##name = name;    \
//        invokeOnPeer(#write, name); \
//        emit notify(name);  \
//    }

////Constructors
//#define N_CLASS_DECLARE(class) \
//    Q_INVOKABLE  class(QObject *parent = 0); \
//    class(AbstractHub *hub, QObject *parent = 0);

//#ifdef NEURONSHAREDOBJECT_H
//#   define N_CLASS_IMPL(class) \
//        class::class(QObject *parent) : SharedObject(parent) \
//        {    }    \
//        class::class(AbstractHub *hub, QObject *parent) : SharedObject(parent)    \
//        {   \
//            if(hub){    \
//                setHub(hub);    \
//                hub->addSharedObject(this); \
//            }   \
//        }
//#else
//#ifdef NEURONPEER_H
//#   define N_CLASS_IMPL(class) \
//        class::class(QObject *parent) : Peer(parent) \
//        {    }    \
//        class::class(AbstractHub *hub, QObject *parent) : Peer(parent)    \
//        {   \
//            if(hub)    \
//                setHub(hub);    \
//        }
//#else
//#   error "No NEURONSHAREDOBJECT_H nor NEURONPEER_H are defined";
//#endif
//#endif

//#endif // SYNTAX_H
