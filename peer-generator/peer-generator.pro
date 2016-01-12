#-------------------------------------------------
#
# Project created by QtCreator 2015-09-28T08:50:29
#
#-------------------------------------------------

QT       += core qml

CONFIG += c++11

TARGET = peer-generator
TEMPLATE = app


SOURCES += main.cpp \
    method.cpp \
    class.cpp \
    classparser.cpp \
    texthelper.cpp \
    property.cpp \
    templatecreatot.cpp

RESOURCES += \
    snippets.qrc

HEADERS += \
    method.h \
    class.h \
    classparser.h \
    texthelper.h \
    property.h \
    templatecreatot.h
