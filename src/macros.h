#ifndef MACROS_H
#define MACROS_H

#define CONCAT_DETAIL(l, r) l##r
#define CONCAT(l, r) CONCAT_DETAIL(l, r)
#define COUNT_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define COUNT_M(...) EXPAND(COUNT_N( __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define VA_NARGS(...) CALL(COUNT_M,(, __VA_ARGS__))
#define CALL(X,Y) X Y
#define EXPAND(...) __VA_ARGS__
#define CALL_N(N, X, V) CALL(CONCAT(N,X),(V))

//DECL
#define METHOD_TOKENS_DECL_1(X,name)		X(void,name,EXPAND(),EXPAND(),EXPAND(),EXPAND())
#define METHOD_TOKENS_DECL_2(X,ret, name)		X(ret,name,EXPAND(),EXPAND(),EXPAND(),EXPAND())
#define METHOD_TOKENS_DECL_3(X,name,a,b)		X(void,name,EXPAND(a b),EXPAND(b),EXPAND(a),EXPAND(,))
#define METHOD_TOKENS_DECL_4(X,ret, name,a,b)		X(ret,name,EXPAND(a b),EXPAND(b),EXPAND(a),EXPAND(,))
#define METHOD_TOKENS_DECL_5(X,name,a,b,c,d)		X(void,name,EXPAND(a b, c d),EXPAND(b,d),EXPAND(a,c),EXPAND(,))
#define METHOD_TOKENS_DECL_6(X,ret, name,a,b,c,d)		X(ret,name,EXPAND(a b, c d),EXPAND(b,d),EXPAND(a,c),EXPAND(,))
#define METHOD_TOKENS_DECL_7(X,name,a,b,c,d,e,f)		X(void,name,EXPAND(a b, c d, e f),EXPAND(b,d,f),EXPAND(a,c,e),EXPAND(,))
#define METHOD_TOKENS_DECL_8(X,ret, name,a,b,c,d,e,f)		X(ret,name,EXPAND(a b, c d, e f),EXPAND(b,d,f),EXPAND(a,c,e),EXPAND(,))
#define METHOD_TOKENS_DECL_9(X,name,a,b,c,d,e,f,g,h)		X(void,name,EXPAND(a b, c d, e f, g h),EXPAND(b,d,f,h),EXPAND(a,c,e,g),EXPAND(,))
#define METHOD_TOKENS_DECL_10(X,ret, name,a,b,c,d,e,f,g,h)		X(ret,name,EXPAND(a b, c d, e f, g h),EXPAND(b,d,f,h),EXPAND(a,c,e,g),EXPAND(,))
#define METHOD_TOKENS_DECL_11(X,name,a,b,c,d,e,f,g,h,i,j)		X(void,name,EXPAND(a b, c d, e f, g h, i j),EXPAND(b,d,f,h,j),EXPAND(a,c,e,g,i),EXPAND(,))
#define METHOD_TOKENS_DECL_12(X,ret, name,a,b,c,d,e,f,g,h,i,j)		X(ret,name,EXPAND(a b, c d, e f, g h, i j),EXPAND(b,d,f,h,j),EXPAND(a,c,e,g,i),EXPAND(,))
#define METHOD_TOKENS_DECL_13(X,name,a,b,c,d,e,f,g,h,i,j,k,l)		X(void,name,EXPAND(a b, c d, e f, g h, i j, k l),EXPAND(b,d,f,h,j,l),EXPAND(a,c,e,g,i,k),EXPAND(,))
#define METHOD_TOKENS_DECL_14(X,ret, name,a,b,c,d,e,f,g,h,i,j,k,l)		X(ret,name,EXPAND(a b, c d, e f, g h, i j, k l),EXPAND(b,d,f,h,j,l),EXPAND(a,c,e,g,i,k),EXPAND(,))
#define METHOD_TOKENS_DECL_15(X,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n)		X(void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n),EXPAND(b,d,f,h,j,l,n),EXPAND(a,c,e,g,i,k,m),EXPAND(,))
#define METHOD_TOKENS_DECL_16(X,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n)		X(ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n),EXPAND(b,d,f,h,j,l,n),EXPAND(a,c,e,g,i,k,m),EXPAND(,))
#define METHOD_TOKENS_DECL_17(X,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)		X(void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p),EXPAND(b,d,f,h,j,l,n,p),EXPAND(a,c,e,g,i,k,m,o),EXPAND(,))
#define METHOD_TOKENS_DECL_18(X,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)		X(ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p),EXPAND(b,d,f,h,j,l,n,p),EXPAND(a,c,e,g,i,k,m,o),EXPAND(,))
#define METHOD_TOKENS_DECL_19(X,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r)		X(void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p, q r),EXPAND(b,d,f,h,j,l,n,p,r),EXPAND(a,c,e,g,i,k,m,o,q),EXPAND(,))
#define METHOD_TOKENS_DECL_20(X,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r)		X(ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p, q r),EXPAND(b,d,f,h,j,l,n,p,r),EXPAND(a,c,e,g,i,k,m,o,q),EXPAND(,))
//IMPL
#define METHOD_TOKENS_IMPL_1(X,class,name)		X(class,void,name,EXPAND(),EXPAND(),EXPAND(),EXPAND())
#define METHOD_TOKENS_IMPL_2(X,class,ret, name)		X(class,ret,name,EXPAND(),EXPAND(),EXPAND(),EXPAND())
#define METHOD_TOKENS_IMPL_3(X,class,name,a,b)		X(class,void,name,EXPAND(a b),EXPAND(b),EXPAND(a),EXPAND(,))
#define METHOD_TOKENS_IMPL_4(X,class,ret, name,a,b)		X(class,ret,name,EXPAND(a b),EXPAND(b),EXPAND(a),EXPAND(,))
#define METHOD_TOKENS_IMPL_5(X,class,name,a,b,c,d)		X(class,void,name,EXPAND(a b, c d),EXPAND(b,d),EXPAND(a,c),EXPAND(,))
#define METHOD_TOKENS_IMPL_6(X,class,ret, name,a,b,c,d)		X(class,ret,name,EXPAND(a b, c d),EXPAND(b,d),EXPAND(a,c),EXPAND(,))
#define METHOD_TOKENS_IMPL_7(X,class,name,a,b,c,d,e,f)		X(class,void,name,EXPAND(a b, c d, e f),EXPAND(b,d,f),EXPAND(a,c,e),EXPAND(,))
#define METHOD_TOKENS_IMPL_8(X,class,ret, name,a,b,c,d,e,f)		X(class,ret,name,EXPAND(a b, c d, e f),EXPAND(b,d,f),EXPAND(a,c,e),EXPAND(,))
#define METHOD_TOKENS_IMPL_9(X,class,name,a,b,c,d,e,f,g,h)		X(class,void,name,EXPAND(a b, c d, e f, g h),EXPAND(b,d,f,h),EXPAND(a,c,e,g),EXPAND(,))
#define METHOD_TOKENS_IMPL_10(X,class,ret, name,a,b,c,d,e,f,g,h)		X(class,ret,name,EXPAND(a b, c d, e f, g h),EXPAND(b,d,f,h),EXPAND(a,c,e,g),EXPAND(,))
#define METHOD_TOKENS_IMPL_11(X,class,name,a,b,c,d,e,f,g,h,i,j)		X(class,void,name,EXPAND(a b, c d, e f, g h, i j),EXPAND(b,d,f,h,j),EXPAND(a,c,e,g,i),EXPAND(,))
#define METHOD_TOKENS_IMPL_12(X,class,ret, name,a,b,c,d,e,f,g,h,i,j)		X(class,ret,name,EXPAND(a b, c d, e f, g h, i j),EXPAND(b,d,f,h,j),EXPAND(a,c,e,g,i),EXPAND(,))
#define METHOD_TOKENS_IMPL_13(X,class,name,a,b,c,d,e,f,g,h,i,j,k,l)		X(class,void,name,EXPAND(a b, c d, e f, g h, i j, k l),EXPAND(b,d,f,h,j,l),EXPAND(a,c,e,g,i,k),EXPAND(,))
#define METHOD_TOKENS_IMPL_14(X,class,ret, name,a,b,c,d,e,f,g,h,i,j,k,l)		X(class,ret,name,EXPAND(a b, c d, e f, g h, i j, k l),EXPAND(b,d,f,h,j,l),EXPAND(a,c,e,g,i,k),EXPAND(,))
#define METHOD_TOKENS_IMPL_15(X,class,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n)		X(class,void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n),EXPAND(b,d,f,h,j,l,n),EXPAND(a,c,e,g,i,k,m),EXPAND(,))
#define METHOD_TOKENS_IMPL_16(X,class,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n)		X(class,ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n),EXPAND(b,d,f,h,j,l,n),EXPAND(a,c,e,g,i,k,m),EXPAND(,))
#define METHOD_TOKENS_IMPL_17(X,class,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)		X(class,void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p),EXPAND(b,d,f,h,j,l,n,p),EXPAND(a,c,e,g,i,k,m,o),EXPAND(,))
#define METHOD_TOKENS_IMPL_18(X,class,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)		X(class,ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p),EXPAND(b,d,f,h,j,l,n,p),EXPAND(a,c,e,g,i,k,m,o),EXPAND(,))
#define METHOD_TOKENS_IMPL_19(X,class,name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r)		X(class,void,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p, q r),EXPAND(b,d,f,h,j,l,n,p,r),EXPAND(a,c,e,g,i,k,m,o,q),EXPAND(,))
#define METHOD_TOKENS_IMPL_20(X,class,ret, name,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r)		X(class,ret,name,EXPAND(a b, c d, e f, g h, i j, k l, m n, o p, q r),EXPAND(b,d,f,h,j,l,n,p,r),EXPAND(a,c,e,g,i,k,m,o,q),EXPAND(,))

#ifdef QT_QML_LIB
#   define CALL_T(t) CallVoid
#else
#   define CALL_T(t) NEURON_WRAP_NAMESPACE(Call)<t>
#endif

//Property
#define N_PROPERTY_DECL(type, name, read, write, notify) \
    private:        \
    Q_PROPERTY(type name READ read WRITE write NOTIFY notify USER true)        \
    protected: \
    type m_##name;\
    public:                                 \
        type read() const; \
    public Q_SLOTS:                         \
    void write(type name); \
    Q_SIGNALS:                              \
    void notify(type name);

#define N_PROPERTY_IMPL(class, type, name, read, write, notify)    \
    type class::read() const{    \
        return m_##name;    \
    } \
    void class::write(type name){ \
        m_##name = name;    \
        invokeOnPeer(#write, QVariant::fromValue(name)); \
        emit notify(name);  \
    }

//Constructors
#define N_CLASS_DECL(class) \
    public: \
    Q_INVOKABLE  class(QObject *parent = nullptr); \
    class(NEURON_WRAP_NAMESPACE(AbstractHub) *hub, QObject *parent = nullptr); \
    private: \
    void initalize();
#ifdef NEURON_SHARED_OBJECT
#define N_CLASS_IMPL(class)                                                     \
        class::class(QObject *parent) : NEURON_WRAP_NAMESPACE(SharedObject)(parent)     \
        {                                                                       \
            setPeerName(#class);                                                \
            initalize();                                                        \
        }                                                                       \
        class::class(NEURON_WRAP_NAMESPACE(AbstractHub) *hub, QObject *parent)  \
                : NEURON_WRAP_NAMESPACE(SharedObject)(parent)                   \
        {                                                                       \
            setPeerName(#class);                                                \
            if(hub)                                                             \
                setHub(hub);                                                    \
            initalize();                                                        \
        }                                                                       \
        void class::initalize()
#else
#define N_CLASS_IMPL(class)                                                     \
        class::class(QObject *parent) : NEURON_WRAP_NAMESPACE(Peer)(parent)     \
        {                                                                       \
            setPeerName(#class);                                                \
            initalize();                                                        \
        }                                                                       \
        class::class(NEURON_WRAP_NAMESPACE(AbstractHub) *hub, QObject *parent)  \
                : NEURON_WRAP_NAMESPACE(Peer)(parent)                           \
        {                                                                       \
            setPeerName(#class);                                                \
            if(hub)                                                             \
                setHub(hub);                                                    \
            initalize();                                                        \
        }                                                                       \
        void class::initalize()
#endif

#define METHOD_CODE_DECL(ret,name,params,names,types,sep) \
    public Q_SLOTS: \
        CALL_T(ret) *name(params); \
        virtual ret name##Slot(params);
#define METHOD_CODE_IMPL(class,ret,name,params,names,types,sep) \
    CALL_T(ret) *class::name(params) \
    {   \
        qlonglong __call_id = invokeOnPeer(#name "Slot" sep names);  \
        auto call = new CALL_T(ret)();    \
        if (__call_id) \
            addCall(__call_id, call);  \
        else \
            call->ignore(); \
        return call; \
    } \
    ret class::name##Slot(params)


#define METHOD_DECL_P(count,...)	CALL(CONCAT(METHOD_TOKENS_DECL_,count),(METHOD_CODE_DECL,__VA_ARGS__))
#define N_REMOTE_METHOD_DECL(...)			METHOD_DECL_P(EXPAND(VA_NARGS(__VA_ARGS__)),EXPAND(__VA_ARGS__))

#define METHOD_IMPL_P(count,...)	CALL(CONCAT(METHOD_TOKENS_IMPL_,count),(METHOD_CODE_IMPL,__VA_ARGS__))
#define N_REMOTE_METHOD_IMPL(class,...)	METHOD_IMPL_P(EXPAND(VA_NARGS(__VA_ARGS__)),EXPAND(class,__VA_ARGS__))

#endif // MACROS_H
