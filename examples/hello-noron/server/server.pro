TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common
INCLUDEPATH += ../../../include

CONFIG += C++11
include(../../../neuron.pri)

DEFINES += NEURON_SERVER

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../common/abstractclient.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    ../common/abstractclient.h \
    ../common/defines.h

