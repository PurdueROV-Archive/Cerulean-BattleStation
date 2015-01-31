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

    /**
     * This is scary. Register things to this, fetch them from QML by name.
     * I don't know if this will work.
     */
    QMap<QString, void*> objects_;


public:
    explicit QMLBattleStationContext(QObject *parent = 0);
    ~QMLBattleStationContext();

signals:

public slots:
};

#endif // QMLBATTLESTATIONCONTEXT_H
