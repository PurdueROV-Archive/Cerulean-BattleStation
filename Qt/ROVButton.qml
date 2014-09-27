import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {
    style: ButtonStyle {
        background: Rectangle {
            border.width: control.activeFocus ? 2 : 1
            color: control.hovered ? "#DDEEFF" : "#00000000"
            radius: 0
            border.color: "#275daf"
            implicitWidth: 70
            implicitHeight: 25
        }
        label: Label {
            text: control.text
            verticalAlignment: Text.AlignVCenter
            color: "#6092dd"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
