#include <QApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtDebug>
#include "godheader.h"
#include "SDL.h"
#undef main

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlEngine engine;
    QMLBattleStationContext* context = new QMLBattleStationContext();
    engine.rootContext()->setContextProperty(QString("context"), context);
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    component.create();
    //  Init/create subsystems
    if (SDL_Init(SDL_INIT_JOYSTICK)) {
        QString* err = new QString(SDL_GetError());
        qWarning() << LOG_ERROR << "SDL init error:" << err;
        //  TODO UI notification
    } else {
        qDebug() << LOG_OK << "SDL init";
    }
    Serial* serial = new Serial();
    InputHandler* inputHandler = new InputHandler();

    //  Connect Serial and BSC
    QObject::connect(context, SIGNAL(SelectedSerialDeviceChanged(QString)),
                     serial, SLOT(SetActiveSerialDevice(QString)));
    //  Connect Input and BSC
    QObject::connect(context, SIGNAL(SelectedJoystickAChanged(QString)),
                     inputHandler, SLOT(SetMainJoystick(QString*)));
    //  Connect Input to Serial
    QObject::connect(inputHandler, SIGNAL(MotorValuesChanged(quint8[])),
                     serial, SLOT(SetMotorValues(quint8[])));
    QObject::connect(inputHandler, SIGNAL(PostToolUpdate(quint16,quint16)),
                     serial, SLOT(EnqueueToolEvent(quint16,quint16)));


    return app.exec();
}
