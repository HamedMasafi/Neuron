QT += network

DEFINES += neuron_SERVER
INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/src/neuronglobal.h \
    $$PWD/src/neuronabstracthub.h \
    $$PWD/src/neuronabstracthub_p.h \
    $$PWD/src/neuronabstractserializer.h \
    $$PWD/src/neuronjsonbinaryserializer.h \
    $$PWD/src/neuronremotecall_p.h \
    $$PWD/src/neuronclienthub.h \
    $$PWD/src/neuronclienthub_p.h \
    $$PWD/src/neuronserverhub.h \
    $$PWD/src/neuronserver.h \
    $$PWD/src/neuronserver_p.h \
    $$PWD/src/neurontcpsocketserver_p.h \
    $$PWD/src/neuronsharedobject.h \
    $$PWD/src/neuronserverhub_p.h \
    $$PWD/src/neuronpeer.h \
    $$PWD/src/neuronserverthread.h \
    $$PWD/src/syntax/syntax.h \
    $$PWD/src/syntax/method_metamethod.h \
    $$PWD/src/syntax/syntax_sharedobject.h \
    $$PWD/src/syntax/syntax_peer.h \
    $$PWD/src/syntax/p_share.h \
    $$PWD/src/syntax/method_jscallback.h \
    $$PWD/src/syntax/method_async.h \
    $$PWD/src/syntax/method_slotcallback.h \
    $$PWD/src/syntax/method_stdfunc.h \
    $$PWD/src/syntax/method_slot_sharedobject.h \
    $$PWD/src/syntax/method_slot_peer.h \
    $$PWD/src/syntax/decl_signal_peer.h \
    $$PWD/src/syntax/decl_signal_sharedobject.h

SOURCES += \
    $$PWD/src/neuronabstracthub.cpp \
    $$PWD/src/neuronabstractserializer.cpp \
    $$PWD/src/neuronjsonbinaryserializer.cpp \
    $$PWD/src/neuronremotecall.cpp \
    $$PWD/src/neuronclienthub.cpp \
    $$PWD/src/neuronserverhub.cpp \
    $$PWD/src/neuronserver.cpp \
    $$PWD/src/neurontcpsocketserver.cpp \
    $$PWD/src/neuronsharedobject.cpp \
    $$PWD/src/neuronpeer.cpp \
    $$PWD/src/neuronserverthread.cpp
