TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common
INCLUDEPATH += ../../../include

include(../../../neuron.pri)

DEFINES += NEURON_CLIENT

SOURCES += \
    ../common/abstractclient.cpp \
    main.cpp \
    clientwindow.cpp

FORMS += \
    clientwindow.ui

HEADERS += \
    ../common/abstractclient.h \
    clientwindow.h \
    ../common/defines.h
