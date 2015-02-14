#include "qmlbattlestationcontext.h"

QMLBattleStationContext::QMLBattleStationContext(QObject *parent) : QObject(parent) {

}

QMLBattleStationContext::~QMLBattleStationContext() {

}

QStringList QMLBattleStationContext::GetSerialDeviceList() {
    return m_serial_device_list;
}

void QMLBattleStationContext::SignalSerialDeviceListChanged() {
    emit SerialDeviceListChanged();
}

void QMLBattleStationContext::SignalSelectedSerialDeviceChanged() {
    emit SelectedSerialDeviceChanged();
}

QStringList QMLBattleStationContext::GetJoystickList() {
    return m_joystick_list;
}

void QMLBattleStationContext::SignalJoystickListChanged() {
    emit JoystickListChanged();
}

void QMLBattleStationContext::SignalSelectedJoystickAChanged() {
    emit SelectedJoystickAChanged();
}

void QMLBattleStationContext::SignalSelectedJoystickBChanged() {
    emit SelectedJoystickBChanged();
}
