TEMPLATE = app

QT += qml quick widgets
INCLUDEPATH += $$PWD/../common

include(../../lib/rpc.pri)

SOURCES += main.cpp\
    ../common/user.cpp \
    ../common/server.cpp \
    pixmap.cpp

HEADERS += \
    ../common/user.h \
    ../common/server.h \
    ../common/defines.h \
    pixmap.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

