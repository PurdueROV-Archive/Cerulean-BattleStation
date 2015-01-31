TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    serial.cpp \
    qmlbattlestationcontext.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serial.h \
    godheader.h \
    qmlbattlestationcontext.h
