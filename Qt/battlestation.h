#ifndef BATTLESTATION_H
#define BATTLESTATION_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>
#include "threadcontroller.h"
#include "mainticker.h"

class BattleStation : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString rovName READ rovName NOTIFY rovNameChanged)

    QGuiApplication* m_app;
    QQmlEngine* m_engine;
    ThreadController* m_mainTickerController;
    MainTicker* m_mainTicker;
    QString m_rovName;
public:
    BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine);

    ~BattleStation();

    bool startUp();
    int exec();

    QString rovName() const {
        return m_rovName;
    }

public slots:
    void startMainThread() {
        emit startMain();
    }
signals:
    void startMain();
    void rovNameChanged(QString name);

};

#endif // BATTLESTATION_H
