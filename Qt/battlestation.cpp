#include "battlestation.h"
#include "mainticker.h"

BattleStation::BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine) {
    app = application;
    engine = qmlEngine;
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = component.create();
    qDebug() << root->objectName();
    mainTickerController = new ThreadController(new MainTicker(10));
    mainTickerController->startThread();
}

int BattleStation::exec()  {
    int exec = app->exec();
    qDebug() << "App ended with exit code " << exec << endl;
    mainTickerController->stopThread();
    return exec;
}

BattleStation::~BattleStation() {
    delete mainTickerController;
}
