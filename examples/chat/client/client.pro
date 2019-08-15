TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common

include(../../../neuron.pri)

SOURCES += \
    main.cpp \
    clientwindow.cpp \
    ../common/user.cpp \
    ../common/serverinstance.cpp

FORMS += \
    clientwindow.ui

HEADERS += \
    clientwindow.h \
    ../common/user.h \
    ../common/serverinstance.h \
    ../common/defines.h
