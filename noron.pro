TEMPLATE = lib
QT += network

win32:{
    contains(QMAKE_TARGET.arch, x86_64):{
        PLATFORM = "win"
        ARCH = "64"
    }else{
        PLATFORM = "win"
        ARCH = "32"
    }
}else{
    BITSIZE = $$system(getconf LONG_BIT)
    if (contains(BITSIZE, 64)) {
        linux*: {
            PLATFORM = "linux"
            ARCH = "64"
        }
        macx*: {
            PLATFORM = "mac"
            ARCH = "64"
        }
    }
    if (contains(BITSIZE, 32)) {
        linux*: {
            PLATFORM = "linux"
            ARCH = "32"
        }
        macx*: {
            PLATFORM = "mac"
            ARCH = "32"
        }
    }
    android: PLATFORM = "android"
    ios: PLATFORM = "ios"
}

DESTDIR     = $$PWD/lib/$$PLATFORM$$ARCH/$${BUILD}

include(noron.pri)

DISTFILES +=
