TEMPLATE = app

QT += qml quick serialport core widgets

SOURCES += main.cpp \
    mainticker.cpp \
    battlestation.cpp \
    threadcontroller.cpp \
    joystick.cpp \
    serial.cpp \
    inputhandler.cpp \
    interpolator.cpp

RESOURCES += qml.qrc

RC_FILE = ROVBattlestation.rc

ICON = ROVBattlestation.icns


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    tickclock.h \
    mainticker.h \
    battlestation.h \
    threadcontroller.h \
    joystick.h \
    serial.h \
    inputhandler.h \
    interpolator.h

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        # x86 / 32-bit Windows define
        LIBS += -L$$PWD/../SDL/lib/x86/ -lSDL2
    } else {
        # x86_64 / 64-bit Window define
        LIBS += -L$$PWD/../SDL/lib/x64/ -lSDL2
    }
}


macx {
    QMAKE_LFLAGS += -F$$PWD/../SDL/lib/x64/
    LIBS += -framework SDL2
}

unix: LIBS += -L$$PWD/../SDL/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../SDL/include
DEPENDPATH += $$PWD/../SDL/include
