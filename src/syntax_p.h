#ifndef SYNTAX_H
#define SYNTAX_H

#define NAMEVALUE2(...)
#define NAMEVALUE4(a, b)                                                    a b
#define NAMEVALUE6(a, b, c, d)                                              NAMEVALUE4(a, b), c d
#define NAMEVALUE8(a, b, c, d, e, f)                                        NAMEVALUE6(a, b, c, d), e f
#define NAMEVALUE10(a, b, c, d, e, f, g, h)                                 NAMEVALUE8(a, b, c, d, e, f, g, h), g h
#define NAMEVALUE12(a, b, c, d, e, f, g, h, i, j)                           NAMEVALUE10(a, b, c, d, e, f, g, h, g, h) i j
#define NAMEVALUE14(a, b, c, d, e, f, g, h, i, j, k, l)                     NAMEVALUE12(a, b, c, d, e, f, g, h, g, h, i, j) k l
#define NAMEVALUE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               NAMEVALUE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m n
#define NAMEVALUE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         NAMEVALUE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o p

#define NAMEVALUE1(...)
#define NAMEVALUE3(a, b)                                                    a b
#define NAMEVALUE5(a, b, c, d)                                              NAMEVALUE4(a, b), c d
#define NAMEVALUE7(a, b, c, d, e, f)                                        NAMEVALUE6(a, b, c, d), e f
#define NAMEVALUE9(a, b, c, d, e, f, g, h)                                  NAMEVALUE8(a, b, c, d, e, f, g, h), g h
#define NAMEVALUE11(a, b, c, d, e, f, g, h, i, j)                           NAMEVALUE10(a, b, c, d, e, f, g, h, g, h) i j
#define NAMEVALUE13(a, b, c, d, e, f, g, h, i, j, k, l)                     NAMEVALUE12(a, b, c, d, e, f, g, h, g, h, i, j) k l
#define NAMEVALUE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               NAMEVALUE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m n
#define NAMEVALUE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         NAMEVALUE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o p


#define PARAMNAME2(...)
#define PARAMNAME4(a, b)                                                    b
#define PARAMNAME6(a, b, c, d)                                              PARAMNAME4(a, b), d
#define PARAMNAME8(a, b, c, d, e, f)                                        PARAMNAME6(a, b, c, d), f
#define PARAMNAME10(a, b, c, d, e, f, g, h)                                 PARAMNAME8(a, b, c, d, e, f, g, h), h
#define PARAMNAME12(a, b, c, d, e, f, g, h, i, j)                           PARAMNAME10(a, b, c, d, e, f, g, h, g, h) j
#define PARAMNAME14(a, b, c, d, e, f, g, h, i, j, k, l)                     PARAMNAME12(a, b, c, d, e, f, g, h, g, h, i, j) l
#define PARAMNAME16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               PARAMNAME14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) n
#define PARAMNAME18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         PARAMNAME16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) p

#define PARAMNAME1(...)
#define PARAMNAME3(a, b)                                                    b
#define PARAMNAME5(a, b, c, d)                                              PARAMNAME4(a, b), d
#define PARAMNAME7(a, b, c, d, e, f)                                        PARAMNAME6(a, b, c, d), f
#define PARAMNAME9(a, b, c, d, e, f, g, h)                                  PARAMNAME8(a, b, c, d, e, f, g, h), h
#define PARAMNAME11(a, b, c, d, e, f, g, h, i, j)                           PARAMNAME10(a, b, c, d, e, f, g, h, g, h) j
#define PARAMNAME13(a, b, c, d, e, f, g, h, i, j, k, l)                     PARAMNAME12(a, b, c, d, e, f, g, h, g, h, i, j) l
#define PARAMNAME15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               PARAMNAME14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) n
#define PARAMNAME17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         PARAMNAME16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) p

#define PARAMTYPE2(...)
#define PARAMTYPE4(a, b)                                                    a
#define PARAMTYPE6(a, b, c, d)                                              PARAMTYPE4(a, b), c
#define PARAMTYPE8(a, b, c, d, e, f)                                        PARAMTYPE6(a, b, c, d), e
#define PARAMTYPE10(a, b, c, d, e, f, g, h)                                 PARAMTYPE8(a, b, c, d, e, f, g, h), g
#define PARAMTYPE12(a, b, c, d, e, f, g, h, i, j)                           PARAMTYPE10(a, b, c, d, e, f, g, h, g, h) i
#define PARAMTYPE14(a, b, c, d, e, f, g, h, i, j, k, l)                     PARAMTYPE12(a, b, c, d, e, f, g, h, g, h, i, j) k
#define PARAMTYPE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               PARAMTYPE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m
#define PARAMTYPE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         PARAMTYPE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o

#define PARAMTYPE1(...)
#define PARAMTYPE3(a, b)                                                    a
#define PARAMTYPE5(a, b, c, d)                                              PARAMTYPE4(a, b), c
#define PARAMTYPE7(a, b, c, d, e, f)                                        PARAMTYPE6(a, b, c, d), e
#define PARAMTYPE9(a, b, c, d, e, f, g, h)                                  PARAMTYPE8(a, b, c, d, e, f, g, h), g
#define PARAMTYPE11(a, b, c, d, e, f, g, h, i, j)                           PARAMTYPE10(a, b, c, d, e, f, g, h, g, h) i
#define PARAMTYPE13(a, b, c, d, e, f, g, h, i, j, k, l)                     PARAMTYPE12(a, b, c, d, e, f, g, h, g, h, i, j) k
#define PARAMTYPE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               PARAMTYPE14(a, b, c, d, e, f, g, h, g, h, i, j, k, l) m
#define PARAMTYPE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         PARAMTYPE16(a, b, c, d, e, f, g, h, g, h, i, j, k, l, m, n) o

#define SEP1
#define SEP2
#define SEP3 				,
#define SEP4 				,
#define SEP5 				,
#define SEP6 				,
#define SEP7 				,
#define SEP8 				,
#define SEP9 				,
#define SEP10 				,
#define SEP11 				,
#define SEP12 				,
#define SEP13 				,
#define SEP14 				,
#define SEP15 				,
#define SEP16 				,

#define RETTYPE0(r)          void
#define RETTYPE1(r)          void
#define RETTYPE2(r)          r
#define RETTYPE3(r)          void
#define RETTYPE4(r)          r
#define RETTYPE5(r)          void
#define RETTYPE6(r)          r
#define RETTYPE7(r)          void
#define RETTYPE8(r)          r
#define RETTYPE9(r)          void
#define RETTYPE10(r)          r
#define RETTYPE11(r)          void
#define RETTYPE12(r)          r
#define RETTYPE13(r)          void
#define RETTYPE14(r)          r
#define RETTYPE15(r)          void
#define RETTYPE16(r)          r

#define PARAMS0()          //r
#define PARAMS1(r)          //r, __VA_ARGS__
#define PARAMS2(r, ...)          __VA_ARGS__
#define PARAMS3(r, ...)          r, __VA_ARGS__
#define PARAMS4(r, ...)          __VA_ARGS__
#define PARAMS5(r, ...)          r, __VA_ARGS__
#define PARAMS6(r, ...)          __VA_ARGS__
#define PARAMS7(r, ...)          r, __VA_ARGS__
#define PARAMS8(r, ...)          __VA_ARGS__
#define PARAMS9(r, ...)          r, __VA_ARGS__
#define PARAMS10(r, ...)          __VA_ARGS__
#define PARAMS11(r, ...)          r, __VA_ARGS__
#define PARAMS12(r, ...)          __VA_ARGS__
#define PARAMS13(r, ...)          r, __VA_ARGS__
#define PARAMS14(r, ...)          __VA_ARGS__
#define PARAMS15(r, ...)          r, __VA_ARGS__
#define PARAMS16(r, ...)          __VA_ARGS__

//#define FUNCNAME0(r)          r
#define FUNCNAME1(r)              r
#define FUNCNAME2(r,n)          n
#define FUNCNAME3(r, name, ...)          r
#define FUNCNAME4(r, name, ...)          name
#define FUNCNAME5(r, name, ...)          r
#define FUNCNAME6(r, name, ...)          name
#define FUNCNAME7(r, name, ...)          r
#define FUNCNAME8(r, name, ...)          name
#define FUNCNAME9(r, name, ...)          r
#define FUNCNAME10(r, name, ...)          name
#define FUNCNAME11(r, name, ...)          r
#define FUNCNAME12(r, name, ...)          name
#define FUNCNAME13(r, name)          r
#define FUNCNAME14(r, name)          name
#define FUNCNAME15(r, name)          r
#define FUNCNAME16(r, name)          name

#define VA_NARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...)     N
#define VA_NARGS(...)                                           VA_NARGS_IMPL(__VA_ARGS__,9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VA_ODDEVEN(...)                                         VA_NARGS_IMPL(__VA_ARGS__,odd, even, odd, even, odd, even, odd, even, odd, even)

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define PARAMS_odd(n, ...)              n, __VA_ARGS__
#define PARAMS_even(n, ...)             __VA_ARGS__

//TODO :

#define FIRST_ARG_(N, ...) N
#define FIRST_ARG(args) FIRST_ARG_ args

#define FUNCNAME_odd(r, ...)             r
#define FUNCNAME_even(r, n, ...)         n

#define RETTYPE_odd(...)                   void
#define RETTYPE_even(r, ...)                  r

#define NAMEVALUE(count, ...)             NAMEVALUE ## count(__VA_ARGS__)
#define PARAMTYPE(count, ...)             PARAMTYPE ## count(__VA_ARGS__)
#define PARAMNAME(count, ...)             PARAMNAME ## count(__VA_ARGS__)
#define SEP(count)                        SEP ## count

#define PARAMS(count, name, ...)          PARAMS ## count(__VA_ARGS__)
#define FUNCNAME(count, ...)              FUNCNAME ## count(__VA_ARGS__)
#define RETTYPE(oddeven, ...)             RETTYPE_ ## oddeven(__VA_ARGS__)

// define methods
#ifndef QT_LIB_QML
#   define NO_QML_CALLBACK
#endif

// void foo(int n);
#ifndef NO_NORMAL
#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...) \
        ret name(NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_NORMAL(class, ret, name, count, sep, ...) \
    ret class::name(NAMEVALUE(count, __VA_ARGS__)) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(NoronRemoteCallBase::EventLoop);    \
            addCall(id, call);  \
            call->eventLoop->exec();    \
            removeCall(id); \
            delete call;    \
        }   \
    }
#else
#   define METHOD_DECL_P_NORMAL(ret, name, count, sep, ...)
#   define METHOD_IMPL_P_NORMAL(class, ret, name, count, sep, ...)
#endif

// void fooAsync(int n);
#ifndef NO_NORMAL_ASYNC
#   define METHOD_DECL_P_ASYNC(ret, name, count, sep, ...) \
        ret name##Async(NAMEVALUE(count, __VA_ARGS__));

#   define METHOD_IMPL_P_ASYNC(class, ret, name, count, sep, ...) \
    ret class::name##Async(NAMEVALUE(count, __VA_ARGS__))   \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(NoronRemoteCallBase::EventLoop);    \
            addCall(id, call);  \
        }   \
    }
#else
#   define METHOD_DECL_P_ASYNC(ret, name, count, sep, ...)
#endif

//void foo(int n, const QObject *obj, const QMetaMethod *callbackMethod);
#ifndef NO_META_METHOD
#   define METHOD_DECL_P_META_METHOD(ret, name, count, sep, ...) \
        ret name(NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod);

#   define METHOD_IMPL_P_META_METHOD(class, ret, name, count, sep, ...) \
    ret class::name(NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, const QMetaMethod *callbackMethod) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            QObject *target = const_cast<QObject *>(obj);   \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod)); \
            addCall(id, call);  \
        }   \
    }
#else
#   define METHOD_DECL_P_META_METHOD(ret, name, count, sep, ...)
#   define METHOD_IMPL_P_META_METHOD(class, ret, name, count, sep, ...)
#endif

//void foo(int n, QJSValue callbackFunction);
#ifndef NO_QML_CALLBACK
#   define METHOD_DECL_P_QML_CALLBACK(ret, name, count, sep, ...) \
        ret name(NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction);

#   define METHOD_IMPL_P_QML_CALLBACK(class, ret, name, count, sep, ...) \
    ret class::name(NAMEVALUE(count, __VA_ARGS__) sep QJSValue callbackFunction)    \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(callbackFunction, hub()->qmlEngine(), hub()->jsEngine());   \
            addCall(id, call);  \
        }   \
    }
#else
#   define METHOD_DECL_P_QML_CALLBACK(ret, name, count, sep, ...)
#   define METHOD_IMPL_P_QML_CALLBACK(class, ret, name, count, sep, ...)
#endif

//void foo(int n, const QObject *obj, char *callbackSlot);
#ifndef NO_SLOT_CALLBACK
#   define METHOD_DECL_P_SLOT_CALLBACK(ret, name, count, sep, ...) \
        Q_INVOKABLE ret name(NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot);

#   define METHOD_IMPL_P_SLOT_CALLBACK(class, ret, name, count, sep, ...) \
    ret class::name(NAMEVALUE(count, __VA_ARGS__) sep const QObject *obj, char *callbackSlot) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(const_cast<QObject *>(obj), callbackSlot);  \
            addCall(id, call);  \
        }   \
    }
#else
#   define METHOD_DECL_P_SLOT_CALLBACK(ret, name, count, sep, ...)
#endif

//int callNumber(int number, std::function<int(void)> callbackFunction);
#ifdef NO_STD_FUNC
#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...) \
        ret name(NAMEVALUE(count, __VA_ARGS__) sep std::function<ret(PARAMTYPE(count, __VA_ARGS__))> callbackFunction);

#   define METHOD_IMPL_P_STD_FUNC(class, ret, name, count, sep, ...) \
    ret class::name(NAMEVALUE(count, __VA_ARGS__) sep std::function<ret(PARAMTYPE(count, __VA_ARGS__))> callbackFunction) \
    {   \
        qlonglong id = invokeOnPeer(#name "Slot" sep PARAMNAME(count, __VA_ARGS));  \
        if(id){ \
            NoronRemoteCallBase *call = new NoronRemoteCallBase(callbackFunction);  \
            addCall(id, call);  \
        }   \
    }
#else
#   define METHOD_DECL_P_STD_FUNC(ret, name, count, sep, ...)
#   define METHOD_IMPL_P_STD_FUNC(class, ret, name, count, sep, ...)
#endif


//signals:
//  void callNumberSignal(int number);
#define METHOD_DECL_P_SIGNAL(ret, name, count, sep, ...) \
        signals: ret name##Signal(NAMEVALUE(count, __VA_ARGS__));




#define REMOTE_METHOD_DECL_P(ret, name, count, oe, ...) \
    ret name(NAMEVALUE(count, __VA_ARGS__)); \
    ret name ## Callback(NAMEVALUE(count, __VA_ARGS__));

#define REMOTE_METHOD_DECL_P3(ret, name, count, oe, ...) \
    public slots: \
    METHOD_DECL_P_NORMAL        (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_ASYNC         (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_META_METHOD   (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_QML_CALLBACK  (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_SLOT_CALLBACK (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_STD_FUNC      (ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_DECL_P_SIGNAL        (ret, name, count, SEP(count), __VA_ARGS__)

#define REMOTE_METHOD_IMPL_P3(class, ret, name, count, oe, ...) \
    METHOD_IMPL_P_NORMAL        (class, ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_ASYNC         (class, ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_META_METHOD   (class, ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_QML_CALLBACK  (class, ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_SLOT_CALLBACK (class, ret, name, count, SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_STD_FUNC      (class, ret, name, count, SEP(count), __VA_ARGS__)

#define REMOTE_METHOD_DECL_P2(count, oe, ...) \
    REMOTE_METHOD_DECL_P3(RETTYPE(oe, __VA_ARGS__), FUNCNAME(count, __VA_ARGS__), count, oe, PARAMS(count, __VA_ARGS__))

#define REMOTE_METHOD_IMPL_P2(class, count, oe, ...) \
    REMOTE_METHOD_IMPL_P3(class, RETTYPE(oe, __VA_ARGS__), FUNCNAME(count, __VA_ARGS__), count, oe, PARAMS(count, __VA_ARGS__))

#define REMOTE_METHOD_DECL(...) \
    REMOTE_METHOD_DECL_P2(PP_NARG(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)

#define REMOTE_METHOD_IMPL(class, ...) \
    REMOTE_METHOD_IMPL_P2(class, PP_NARG(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)



#endif // SYNTAX_H
