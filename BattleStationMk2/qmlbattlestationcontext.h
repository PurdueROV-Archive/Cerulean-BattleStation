#ifndef QMLBATTLESTATIONCONTEXT_H
#define QMLBATTLESTATIONCONTEXT_H

#include <QObject>
#include <QMap>

/**
 * This class is the mediator between C++ code and QML.
 * We will only directly expose this class to QML through
 * setContextProperty().
 */
class QMLBattleStationContext : public QObject
{
    Q_OBJECT

    //  I have come to a conclusion that using a map won't work. ~Vince

public:
    explicit QMLBattleStationContext(QObject *parent = 0);
    ~QMLBattleStationContext();

signals:
    void ObjectsChanged();
public slots:

};

#endif // QMLBATTLESTATIONCONTEXT_H
