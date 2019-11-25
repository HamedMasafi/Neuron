#ifndef NEURONSYNTAX_H
#define NEURONSYNTAX_H

#include <QtGlobal>

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG("-Wgnu-zero-variadic-macro-arguments")
QT_WARNING_DISABLE_CLANG("-Wreserved-id-macro")
QT_WARNING_DISABLE_GCC("-Wpedantic")

#ifdef QT_QML_LIB
#define CALL(t) CallVoid
#else
#define CALL(t) NEURON_WRAP_NAMESPACE(Call)<t>
#endif

#include "p_share.h"
#include "method_normal.h"
#include "decl_signal_peer.h"

#define RET_TYPE_VOID(ret) void
#define RET_TYPE_NONVOID(ret) ret
#define RET_TYPE(oe, ret) RET_TYPE_##oe(ret)

#define __REMOTE_METHOD_DECL_P3(ret, name, count, oe, ...) \
    public Q_SLOTS: \
        CALL(ret) *name(__NAMEVALUE(count, __VA_ARGS__)); \
        METHOD_DECL_P_SLOT          (ret, name, count, __SEP(count), __VA_ARGS__) \
    Q_SIGNALS: \
        METHOD_DECL_P_SIGNAL_##oe   (ret, name, count, __SEP(count), __VA_ARGS__)

#define __REMOTE_METHOD_IMPL_P3(class, ret, name, count, oe, ...) \
    METHOD_IMPL_P_NORMAL            (class, ret, name, count, __SEP(count), __VA_ARGS__) \
    METHOD_IMPL_P_SLOT_##oe         (class, ret, name, count, __SEP(count), __VA_ARGS__)

#define __REMOTE_METHOD_DECL_P2(count, oe, ...) \
    __REMOTE_METHOD_DECL_P3(       __RETTYPE(oe, __VA_ARGS__), __FUNCNAME(count, __VA_ARGS__), count, oe, __PARAMS(count, __VA_ARGS__))

#define __REMOTE_METHOD_IMPL_P2(class, count, oe, ...) \
    __REMOTE_METHOD_IMPL_P3(class, __RETTYPE(oe, __VA_ARGS__), __FUNCNAME(count, __VA_ARGS__), count, oe, __PARAMS(count, __VA_ARGS__))

//User macros
#define N_REMOTE_METHOD_DECL(...) \
    __REMOTE_METHOD_DECL_P2(       VA_NARGS(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)

#define N_REMOTE_METHOD_IMPL(class, ...) \
    __REMOTE_METHOD_IMPL_P2(class, VA_NARGS(__VA_ARGS__), VA_ODDEVEN(__VA_ARGS__), __VA_ARGS__)

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

#define NEURON_SEND_TO_PEER(...) invokeOnPeer(__func__ "Slot", __VA_ARGS__)

QT_WARNING_POP

#endif // NEURONSYNTAX_H
