#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "battlestation.h"

int main(int argc, char *argv[])
{
    qDebug() << "Starting BattleStation...";
    QGuiApplication app(argc, argv);
    QQmlEngine engine;
    BattleStation battlestation(&app, &engine);
    battlestation.startMainThread();
    return battlestation.exec();
}

