import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {
    style: ButtonStyle {
        background: Rectangle {
            border.width: (control.hovered || control.pressed) ? 2 : 1
            color: (control.hovered || control.pressed) ? "#333333" : "#00000000"
            radius: 0
            border.color: mainColor
            implicitWidth: 70
            implicitHeight: 25
        }
        label: Label {
            text: control.text
            verticalAlignment: Text.AlignVCenter
            color: mainColor
            font.bold: true
            font.pixelSize: 30
            font.family: "Arial"
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
