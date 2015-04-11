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

    //  SDL
    if (SDL_Init(SDL_INIT_JOYSTICK)) {
        QString* err = new QString(SDL_GetError());
        qWarning() << LOG_ERROR << "SDL init error:" << err;
        //  TODO UI notification
    } else {
        qDebug() << LOG_OK << "SDL init";
    }

    //  Serial
    Serial* serial = new Serial();



    return app.exec();
}
