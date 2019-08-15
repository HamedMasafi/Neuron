TEMPLATE = app
QT += widgets
INCLUDEPATH += $$PWD/../common

include(../../../neuron.pri)

DEFINES += NEURON_SERVER
SOURCES += \
    ../common/serverinstance.cpp \
    main.cpp \
    mainwindow.cpp \
    ../common/user.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    ../common/serverinstance.h \
    mainwindow.h \
    ../common/user.h \
    ../common/defines.h

