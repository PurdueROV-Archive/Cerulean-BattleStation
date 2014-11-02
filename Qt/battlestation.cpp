#include <QQmlContext>
#include "battlestation.h"
#include "joystick.h"
#include "serial.h"

BattleStation::BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine) {
    m_app = application;
    m_engine = qmlEngine;
    m_rovName = QString("ROV Incompetence");
}

bool BattleStation::startUp() {
    QString* initSDLResult = Joystick::initSDL();
    if(initSDLResult != NULL) {
        qWarning() << "SDL failed to initialize";
        return false;
    }
    serial::initSerial();
    m_mainTicker = new MainTicker(10);
    m_mainTickerController = new ThreadController(m_mainTicker);
    m_engine->rootContext()->setContextProperty("c_battlestation", this);

    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = component.create();
    qDebug() << "Root scene name: " << root->objectName();

    m_mainTickerController->startThread();
    return true;
}

int BattleStation::exec()  {
    int exec = m_app->exec();
    qDebug() << "App ended with exit code " << exec << endl;
    m_mainTickerController->stopThread();
    return exec;
}

BattleStation::~BattleStation() {
    delete m_mainTickerController;
}
