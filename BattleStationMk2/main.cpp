#include <QApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "qmlbattlestationcontext.h"
#include "serial.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlEngine engine;
    QMLBattleStationContext context;
    Serial serial;
    context.SetObject("serial", &serial);
    engine.rootContext()->setContextProperty(QString("context"), &context);
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    component.create();
    return app.exec();
}
