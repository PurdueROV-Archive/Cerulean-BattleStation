#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include "godheader.h"

/**
 * Establishes and maintains the serial connection to the robot.
 */
class Serial : public QObject
{
    Q_OBJECT

    /** Mutex lock to ensure singular access to control_packet_ */
    QMutex m_packet_mutex;

    /** Mutex lock to ensure singular access to the tool queue */
    QMutex m_tool_mutex;

    /** A queue containing transformations to SerialControlPacket::toolBits */
    QQueue<quint32> m_tool_events;
    /** The singleton control packet we use. Make a copy to send values */
    SerialControlPacket m_control_packet;

    /** The serial port over which we communicate */
    QSerialPort* m_serial_port;

    /** An array to remap internal motor IDs to wire IDs */
    quint8 m_motor_mapping[8];


public:
    explicit Serial(QObject *parent = 0);
    ~Serial();

    /**
     * Opens the serial port with the given name.
     * Returns true if successful, false otherwise. Call GetError() for details.
     */
    bool Open(QString deviceName, int newParameter = 19200);

    /**
     * Gets the last error, or QSerialPort::NoError if no error.
     */
    SerialPortError GetError();

    /**
     * Set the current motor values. Value changes are not guaranteed to be sent immediately
     * and can be overwritten by later calls to this function if the Serial Network Thread has
     * not yet sent out another SerialControlPacket. Can be called from any thread.
     * @param values[] An array of 8 bit values encoded as per the packet spec. Len = 8 = num motors
     */
    void SetMotorValues(quint8 values[]);
    /**
     * Enqueues a change to the tool bits. Assuming the connection does not fail, each change will be
     * sent independently, but not necessarily immediately. Can be called from any thread.
     */
    void EnqueueToolEvent(quint16 value, quint16 mask);

    /**
     * Performs a network update pulse. This should NOT be on the UI thread.
     * If serial is not connected, then search for a connection and update the candidate list.
     * If the candidate list is zero, do nothing; if it has one element, set it as the active
     * serial; if there are more than one then let the user select it from the dropdown.
     * ##TENATIVE##
     * If connected, each pulse sends out a control packet with the latest motor values and whatever tool updates that
     * can be sent, so long as two update events cannot interfere (e.g. claw close and claw open cannot
     * be sent simultaneously, but claw open and light on can be).
     */
    void NetworkTick();

signals:

public slots:
};

#endif // SERIAL_H
