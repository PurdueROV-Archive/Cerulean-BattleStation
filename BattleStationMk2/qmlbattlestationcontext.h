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
    Q_PROPERTY(QMap<QString, void *> objects READ Objects NOTIFY ObjectsChanged)

    /**
     * This is scary. Register things to this, fetch them from QML by name.
     * I don't know if this will work.
     */
    QMap<QString, void *> m_objects;


public:
    explicit QMLBattleStationContext(QObject *parent = 0);
    ~QMLBattleStationContext();

    void SetObject(QString name, void * object) {
        m_objects.insert(name, &object);
    }

    /**
     * Objects property getter
     */
    QMap<QString, void*> Objects() const {
        return m_objects;
    }

signals:
    void ObjectsChanged();
public slots:

};

#endif // QMLBATTLESTATIONCONTEXT_H
