QT += network

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/src/global.h \
    $$PWD/src/abstracthub.h \
    $$PWD/src/abstracthub_p.h \
    $$PWD/src/abstractserializer.h \
    $$PWD/src/jsonbinaryserializer.h \
    $$PWD/src/call.h \
    $$PWD/src/abstractcall.h \
    $$PWD/src/clienthub.h \
    $$PWD/src/clienthub_p.h \
    $$PWD/src/serverhub.h \
    $$PWD/src/server.h \
    $$PWD/src/server_p.h \
    $$PWD/src/tcpsocketserver_p.h \
    $$PWD/src/sharedobject.h \
    $$PWD/src/serverhub_p.h \
    $$PWD/src/peer.h \
    $$PWD/src/serverthread.h \
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
    $$PWD/src/syntax/decl_signal_sharedobject.h \
    $$PWD/src/abstractdataencoder.h \
    $$PWD/src/simpletokenvalidator.h

SOURCES += \
    $$PWD/src/abstracthub.cpp \
    $$PWD/src/abstractserializer.cpp \
    $$PWD/src/jsonbinaryserializer.cpp \
    $$PWD/src/call.cpp \
    $$PWD/src/abstractcall.cpp \
    $$PWD/src/clienthub.cpp \
    $$PWD/src/serverhub.cpp \
    $$PWD/src/server.cpp \
    $$PWD/src/tcpsocketserver.cpp \
    $$PWD/src/sharedobject.cpp \
    $$PWD/src/peer.cpp \
    $$PWD/src/serverthread.cpp \
    $$PWD/src/abstractdataencoder.cpp \
    $$PWD/src/simpletokenvalidator.cpp
