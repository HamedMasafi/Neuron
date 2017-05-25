#define __NAMEVALUE2(...)
#define __NAMEVALUE4(a, b)                                                    a b
#define __NAMEVALUE6(a, b, c, d)                                              __NAMEVALUE4(a, b), c d
#define __NAMEVALUE8(a, b, c, d, e, f)                                        __NAMEVALUE6(a, b, c, d), e f
#define __NAMEVALUE10(a, b, c, d, e, f, g, h)                                 __NAMEVALUE8(a, b, c, d, e, f), g h
#define __NAMEVALUE12(a, b, c, d, e, f, g, h, i, j)                           __NAMEVALUE10(a, b, c, d, e, f, g, h) i j
#define __NAMEVALUE14(a, b, c, d, e, f, g, h, i, j, k, l)                     __NAMEVALUE12(a, b, c, d, e, f, g, h, i, j) k l
#define __NAMEVALUE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __NAMEVALUE14(a, b, c, d, e, f, g, h, i, j, k, l) m n
#define __NAMEVALUE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __NAMEVALUE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) o p

#define __NAMEVALUE1(...)
#define __NAMEVALUE3(a, b)                                                    a b
#define __NAMEVALUE5(a, b, c, d)                                              __NAMEVALUE4(a, b), c d
#define __NAMEVALUE7(a, b, c, d, e, f)                                        __NAMEVALUE6(a, b, c, d), e f
#define __NAMEVALUE9(a, b, c, d, e, f, g, h)                                  __NAMEVALUE8(a, b, c, d, e, f), g h
#define __NAMEVALUE11(a, b, c, d, e, f, g, h, i, j)                           __NAMEVALUE10(a, b, c, d, e, f, g, h) i j
#define __NAMEVALUE13(a, b, c, d, e, f, g, h, i, j, k, l)                     __NAMEVALUE12(a, b, c, d, e, f, g, h, i, j) k l
#define __NAMEVALUE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __NAMEVALUE14(a, b, c, d, e, f, g, h, i, j, k, l) m n
#define __NAMEVALUE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __NAMEVALUE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) o p


#define __PARAMNAME2(...)
#define __PARAMNAME4(a, b)                                                    b
#define __PARAMNAME6(a, b, c, d)                                              __PARAMNAME4(a, b), d
#define __PARAMNAME8(a, b, c, d, e, f)                                        __PARAMNAME6(a, b, c, d), f
#define __PARAMNAME10(a, b, c, d, e, f, g, h)                                 __PARAMNAME8(a, b, c, d, e, f), h
#define __PARAMNAME12(a, b, c, d, e, f, g, h, i, j)                           __PARAMNAME10(a, b, c, d, e, f, g, h) j
#define __PARAMNAME14(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMNAME12(a, b, c, d, e, f, g, h, i, j) l
#define __PARAMNAME16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMNAME14(a, b, c, d, e, f, g, h, i, j, k, l) n
#define __PARAMNAME18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMNAME16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) p

#define __PARAMNAME1(...)
#define __PARAMNAME3(a, b)                                                    b
#define __PARAMNAME5(a, b, c, d)                                              __PARAMNAME4(a, b), d
#define __PARAMNAME7(a, b, c, d, e, f)                                        __PARAMNAME6(a, b, c, d), f
#define __PARAMNAME9(a, b, c, d, e, f, g, h)                                  __PARAMNAME8(a, b, c, d, e, f), h
#define __PARAMNAME11(a, b, c, d, e, f, g, h, i, j)                           __PARAMNAME10(a, b, c, d, e, f, g, h) j
#define __PARAMNAME13(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMNAME12(a, b, c, d, e, f, g, h, i, j) l
#define __PARAMNAME15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMNAME14(a, b, c, d, e, f, g, h, i, j, k, l) n
#define __PARAMNAME17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMNAME16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) p

#define __PARAMTYPE2(...)
#define __PARAMTYPE4(a, b)                                                    a
#define __PARAMTYPE6(a, b, c, d)                                              __PARAMTYPE4(a, b), c
#define __PARAMTYPE8(a, b, c, d, e, f)                                        __PARAMTYPE6(a, b, c, d), e
#define __PARAMTYPE10(a, b, c, d, e, f, g, h)                                 __PARAMTYPE8(a, b, c, d, e, f), g
#define __PARAMTYPE12(a, b, c, d, e, f, g, h, i, j)                           __PARAMTYPE10(a, b, c, d, e, f, g, h) i
#define __PARAMTYPE14(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMTYPE12(a, b, c, d, e, f, g, h, i, j) k
#define __PARAMTYPE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMTYPE14(a, b, c, d, e, f, g, h, i, j, k, l) m
#define __PARAMTYPE18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMTYPE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) o

#define __PARAMTYPE1(...)
#define __PARAMTYPE3(a, b)                                                    a
#define __PARAMTYPE5(a, b, c, d)                                              __PARAMTYPE4(a, b), c
#define __PARAMTYPE7(a, b, c, d, e, f)                                        __PARAMTYPE6(a, b, c, d), e
#define __PARAMTYPE9(a, b, c, d, e, f, g, h)                                  __PARAMTYPE8(a, b, c, d, e, f), g
#define __PARAMTYPE11(a, b, c, d, e, f, g, h, i, j)                           __PARAMTYPE10(a, b, c, d, e, f, g, h) i
#define __PARAMTYPE13(a, b, c, d, e, f, g, h, i, j, k, l)                     __PARAMTYPE12(a, b, c, d, e, f, g, h, i, j) k
#define __PARAMTYPE15(a, b, c, d, e, f, g, h, i, j, k, l, m, n)               __PARAMTYPE14(a, b, c, d, e, f, g, h, i, j, k, l) m
#define __PARAMTYPE17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)         __PARAMTYPE16(a, b, c, d, e, f, g, h, i, j, k, l, m, n) o

#define __SEP1
#define __SEP2
#define __SEP3 				,
#define __SEP4 				,
#define __SEP5 				,
#define __SEP6 				,
#define __SEP7 				,
#define __SEP8 				,
#define __SEP9 				,
#define __SEP10 			,
#define __SEP11 			,
#define __SEP12 			,
#define __SEP13 			,
#define __SEP14 			,
#define __SEP15 			,
#define __SEP16 			,

#define __RETTYPE0(r)           void
#define __RETTYPE1(r)           void
#define __RETTYPE2(r)           r
#define __RETTYPE3(r)           void
#define __RETTYPE4(r)           r
#define __RETTYPE5(r)           void
#define __RETTYPE6(r)           r
#define __RETTYPE7(r)           void
#define __RETTYPE8(r)           r
#define __RETTYPE9(r)           void
#define __RETTYPE10(r)          r
#define __RETTYPE11(r)          void
#define __RETTYPE12(r)          r
#define __RETTYPE13(r)          void
#define __RETTYPE14(r)          r
#define __RETTYPE15(r)          void
#define __RETTYPE16(r)          r

#define __PARAMS0()             //r
#define __PARAMS1(r)            //r, __VA_ARGS__
#define __PARAMS2(...)          __VA_ARGS__
#define __PARAMS3(r, ...)       r, __VA_ARGS__
#define __PARAMS4(r, ...)       __VA_ARGS__
#define __PARAMS5(r, ...)       r, __VA_ARGS__
#define __PARAMS6(r, ...)       __VA_ARGS__
#define __PARAMS7(r, ...)       r, __VA_ARGS__
#define __PARAMS8(r, ...)       __VA_ARGS__
#define __PARAMS9(r, ...)       r, __VA_ARGS__
#define __PARAMS10(r, ...)      __VA_ARGS__
#define __PARAMS11(r, ...)      r, __VA_ARGS__
#define __PARAMS12(r, ...)      __VA_ARGS__
#define __PARAMS13(r, ...)      r, __VA_ARGS__
#define __PARAMS14(r, ...)      __VA_ARGS__
#define __PARAMS15(r, ...)      r, __VA_ARGS__
#define __PARAMS16(r, ...)      __VA_ARGS__

//#define __FUNCNAME0(r)            r
#define __FUNCNAME1(r)              r
#define __FUNCNAME2(r,n)            n
#define __FUNCNAME3(r, name, ...)   r
#define __FUNCNAME4(r, name, ...)   name
#define __FUNCNAME5(r, name, ...)   r
#define __FUNCNAME6(r, name, ...)   name
#define __FUNCNAME7(r, name, ...)   r
#define __FUNCNAME8(r, name, ...)   name
#define __FUNCNAME9(r, name, ...)   r
#define __FUNCNAME10(r, name, ...)  name
#define __FUNCNAME11(r, name, ...)  r
#define __FUNCNAME12(r, name, ...)  name
#define __FUNCNAME13(r, name)       r
#define __FUNCNAME14(r, name)       name
#define __FUNCNAME15(r, name)       r
#define __FUNCNAME16(r, name)       name

#define VA_NARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...)         N
#define VA_NARGS(...)               VA_NARGS_IMPL(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VA_ODDEVEN(...)             VA_NARGS_IMPL(__VA_ARGS__, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID,VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID, VOID, NONVOID)

#define __FUNCNAME_VOID(r, ...)             r
#define __FUNCNAME_NONVOID(r, n, ...)       n

#define __RETTYPE_VOID(...)                 void
#define __RETTYPE_NONVOID(r, ...)           r

#define __NAMEVALUE(count, ...)             __NAMEVALUE ## count(__VA_ARGS__)
#define __PARAMTYPE(count, ...)             __PARAMTYPE ## count(__VA_ARGS__)
#define __PARAMNAME(count, ...)             __PARAMNAME ## count(__VA_ARGS__)
#define __SEP(count)                        __SEP ## count

#define __PARAMS(count, name, ...)          __PARAMS ## count(__VA_ARGS__)
#define __FUNCNAME(count, ...)              __FUNCNAME ## count(__VA_ARGS__)
#define __RETTYPE(oddeven, ...)             __RETTYPE_ ## oddeven(__VA_ARGS__)
