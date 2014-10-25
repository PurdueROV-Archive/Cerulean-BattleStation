#ifndef BATTLESTATION_H
#define BATTLESTATION_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>
#include "threadcontroller.h"

class BattleStation : public QObject {
    Q_OBJECT

    QGuiApplication* app;
    QQmlEngine* engine;
    ThreadController* mainTickerController;
public:
    BattleStation(QGuiApplication* application, QQmlEngine* qmlEngine);

    ~BattleStation();

    bool startUp();
    int exec();

public slots:
    void startMainThread() {
        emit startMain();
    }
signals:
    void startMain();

};

#endif // BATTLESTATION_H
