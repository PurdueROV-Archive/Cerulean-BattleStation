#include <QApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "godheader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlEngine engine;
    QMLBattleStationContext context;
    engine.rootContext()->setContextProperty(QString("context"), &context);
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    component.create();
    return app.exec();
}
