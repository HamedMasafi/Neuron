TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common

include(../../../noron.pri)

SOURCES += \
    main.cpp \
    clientwindow.cpp \
    ../common/client.cpp

FORMS += \
    clientwindow.ui

HEADERS += \
    clientwindow.h \
    ../common/client.h \
    ../common/defines.h
