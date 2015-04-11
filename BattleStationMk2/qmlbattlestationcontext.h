#ifndef QMLBATTLESTATIONCONTEXT_H
#define QMLBATTLESTATIONCONTEXT_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QMutex>
#include <QMutexLocker>

/**
 * This class is the mediator between C++ code and QML.
 * We will only directly expose this class to QML through
 * setContextProperty().
 */
class QMLBattleStationContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList serialDeviceList READ GetSerialDeviceList NOTIFY SerialDeviceListChanged)
    Q_PROPERTY(QString selectedSerialDevice MEMBER m_selected_serial_device NOTIFY SelectedSerialDeviceChanged)

    Q_PROPERTY(QStringList joystickList READ GetJoystickList NOTIFY JoystickListChanged)
    Q_PROPERTY(QString selectedJoystickA MEMBER m_selected_joystick_a NOTIFY SelectedJoystickAChanged)
    Q_PROPERTY(QString selectedJoystickB MEMBER m_selected_joystick_b NOTIFY SelectedJoystickBChanged)


    //  I have come to a conclusion that using a map won't work. ~Vince

public:

    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    //  SERIAL DEVICE PROPERTIES                            //
    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    /**
     * A list of the available serial devices available on the system.
     * ACQUIRE m_serial_device_mutex BEFORE CHANGING!
     * CALL SignalSerialDeviceListChanged() AFTER CHANGES BEFORE RELEASING MUTEX!
     */
    QStringList m_serial_device_list;
    /**
     * The currently active/selected serial device. Empty if none.
     * ACQUIRE m_serial_device_mutex BEFORE CHANGING!
     * CALL SignalSelectedSerialDeviceChanged() AFTER CHANGES BEFORE RELEASING MUTEX!
     */
    QString m_selected_serial_device;
    /**
     * The mutex used to allow multithreaded access to the serial device members.
     */
    QMutex m_serial_device_mutex;

    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    //  JOYSTICK PROPERTIES                                 //
    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    /**
     * A list of al the joysticks available on the system.
     * ACQUIRE m_joystick_mutex BEFORE CHANGING!
     */
    QStringList m_joystick_list;
    /**
     * The currently active/selected primary joystick (A). Empty if none.
     * ACQUIRE m_joystick_mutex BEFORE CHANGING!
     */
    QString m_selected_joystick_a;
    /**
     * The currently active/selected secondary joystick (B). Empty if none.
     * ACQUIRE m_joystick_mutex BEFORE CHANGING!
     */
    QString m_selected_joystick_b;
    /**
     * The mutex used to allow multithreaded access to the joystick members.
     */
    QMutex m_joystick_mutex;



    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    //  FUNCTIONS                                           //
    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //

    explicit QMLBattleStationContext(QObject *parent = 0);
    ~QMLBattleStationContext();

    /**
     * QML USE ONLY.
     * Gets the list of available serial devices on the system.
     */
    QStringList GetSerialDeviceList();
    /**
     * Notifies QML that the serial device list has changed.
     * Call after making changes to the Serial Device List.
     */
    void SignalSerialDeviceListChanged();
    /**
     * Notifies QML that the selected serial device has changed.
     * Call after making changes to the Selected Serial Device
     */
    void SignalSelectedSerialDeviceChanged();

    /**
     * QML USE ONLY.
     * Gets the list of available joysticks on the system.
     */
    QStringList GetJoystickList();
    /**
     * Notifies QML that the joystick list has changed.
     * Call after making changes to the Joystick List.
     */
    void SignalJoystickListChanged();
    /**
     * Notifies QML that the selected primary joystick (A) has changed.
     * Call after making changes to the Selected Primary Joystick (A)
     */
    void SignalSelectedJoystickAChanged();
    /**
     * Notifies QML that the selected secondary joystick (B) has changed.
     * Call after making changes to the Selected Secondary Joystick (B)
     */
    void SignalSelectedJoystickBChanged();

signals:
    void SerialDeviceListChanged();
    void SelectedSerialDeviceChanged(QString name);
    void JoystickListChanged();
    void SelectedJoystickAChanged(QString name);
    void SelectedJoystickBChanged(QString name);
public slots:

};

#endif // QMLBATTLESTATIONCONTEXT_H
