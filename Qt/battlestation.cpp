#include <QQmlContext>
#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include "battlestation.h"
#include "joystick.h"
#include "serial.h"

BattleStation::BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine) {
    m_app = application;
    m_engine = qmlEngine;
    m_rovName = QString("ROV Incompetence");
}

bool BattleStation::startUp() {
    //  Must register in Qt's type system for joystick use
    qRegisterMetaType<Sint16>("Sint16");
    QString* initSDLResult = Joystick::initSDL();
    if(initSDLResult != NULL) {
        qWarning() << "SDL failed to initialize";
        return false;
    }

    m_mainTicker = new MainTicker(100);
    m_mainTickerController = new ThreadController(m_mainTicker);
    m_engine->rootContext()->setContextProperty("c_battlestation", this);
    m_mainTicker->registerInContext(m_engine->rootContext());

    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/main.qml")));
    root = component.create();
    qDebug() << "Root scene name: " << root->objectName();

    //serial::initSerial("FT231X USB UART"); //OS X
    serial::initSerial(root, "USB Serial Port");  //Windows

    QObject* horizontalControl = root->findChild<QObject*>("horizontalControl");
    qDebug() << horizontalControl->property("value");

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
