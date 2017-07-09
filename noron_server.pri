QT += network

DEFINES += NORON_SERVER
INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/src/noronglobal.h \
    $$PWD/src/noronabstracthub.h \
    $$PWD/src/noronabstracthub_p.h \
    $$PWD/src/noronabstractserializer.h \
    $$PWD/src/noronjsonbinaryserializer.h \
    $$PWD/src/noronremotecall_p.h \
    $$PWD/src/noronclienthub.h \
    $$PWD/src/noronclienthub_p.h \
    $$PWD/src/noronserverhub.h \
    $$PWD/src/noronserver.h \
    $$PWD/src/noronserver_p.h \
    $$PWD/src/norontcpsocketserver_p.h \
    $$PWD/src/noronsharedobject.h \
    $$PWD/src/noronserverhub_p.h \
    $$PWD/src/noronpeer.h \
    $$PWD/src/noronserverthread.h \
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
    $$PWD/src/noronabstracthub.cpp \
    $$PWD/src/noronabstractserializer.cpp \
    $$PWD/src/noronjsonbinaryserializer.cpp \
    $$PWD/src/noronremotecall.cpp \
    $$PWD/src/noronclienthub.cpp \
    $$PWD/src/noronserverhub.cpp \
    $$PWD/src/noronserver.cpp \
    $$PWD/src/norontcpsocketserver.cpp \
    $$PWD/src/noronsharedobject.cpp \
    $$PWD/src/noronpeer.cpp \
    $$PWD/src/noronserverthread.cpp
