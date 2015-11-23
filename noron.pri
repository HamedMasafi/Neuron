QT += network

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/src/noronhub.h \
    $$PWD/src/noronpeer.h \
    $$PWD/src/noronserver.h \
    $$PWD/src/norontcpsocketserver_p.h \
    $$PWD/src/noronglobal.h \
    $$PWD/src/noronhubbase.h \
    $$PWD/src/noronremotecall_p.h \
    $$PWD/src/noronserializerbase_p.h \
    $$PWD/src/noronjsondataserializer.h \
    $$PWD/src/noronhubbase_p.h \
    $$PWD/src/noronserver_p.h \
    $$PWD/src/noronhub_p.h

SOURCES += \
    $$PWD/src/noronhub.cpp \
    $$PWD/src/noronpeer.cpp \
    $$PWD/src/noronserver.cpp \
    $$PWD/src/norontcpsocketserver.cpp \
    $$PWD/src/noronhubbase.cpp \
    $$PWD/src/noronremotecall.cpp \
    $$PWD/src/noronserializerbase.cpp \
    $$PWD/src/noronjsondataserializer.cpp


