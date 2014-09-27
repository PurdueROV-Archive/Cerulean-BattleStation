#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QVariant>
#include <QMetaObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *object = component.create();

    QVariant returnedValue;
    QVariant msg = "ELLO MATE";
    QMetaObject::invokeMethod(object, "testFunction", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg));

    qDebug() << "TEST " << returnedValue.toString();

    return app.exec();
}


