#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "battlestation.h"

int main(int argc, char *argv[])
{
    qDebug() << "Starting BattleStation...";
    QGuiApplication app(argc, argv);
    QQmlEngine engine;
    BattleStation* battlestation = new BattleStation(&app, &engine);
    int ret = -1;
    if (battlestation->startUp()) {
        ret = battlestation->exec();
    }

    delete battlestation;
    return ret;
}

