import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


CheckBox {
    x: 10
    id: checkTask
    property int size: (missionTasksTab.width < 550) ? 16 : 20;


    style: CheckBoxStyle {

        indicator: Rectangle {
            implicitWidth: size
            implicitHeight: size
            radius: 1
            border.width: 1
            Rectangle {
                visible: control.checked
                color: "#555"
                radius: 1
                anchors.margins: 4
                anchors.fill: parent
            }
        }


        label: Text {
            id: taskLabel
            color: checkTask.checked ? "#666666" : "#ffffff"
            font.pixelSize: size
            text: checkTask.text
            font.bold: !checkTask.checked
        }
    }
}
