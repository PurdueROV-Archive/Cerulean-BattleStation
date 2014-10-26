#include "battlestation.h"
#include "mainticker.h"
#include "joystick.h"
#include "serial.h"

BattleStation::BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine) {
    app = application;
    engine = qmlEngine;
}

bool BattleStation::startUp() {
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = component.create();
    qDebug() << "Root scene name: " << root->objectName();
    QString* initSDLResult = Joystick::initSDL();
    if(initSDLResult != NULL) {
        qWarning() << "SDL failed to initialize";
        return false;
    }
    mainTickerController = new ThreadController(new MainTicker(10));
    mainTickerController->startThread();
    serial::initSerial();
    return true;
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
