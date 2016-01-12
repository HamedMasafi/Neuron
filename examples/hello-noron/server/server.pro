TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common

CONFIG += C++11
include(../../../noron.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../common/client.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    ../common/client.h \
    ../common/defines.h

