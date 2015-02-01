import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: sysViewArea
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    clip: true

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysTitle
        text: "SYSTEM VIEW"
    }

    Grid {
        id: grid1
        width: 365
        height: 365
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
        columns: 2
        rows: 2
        spacing: 125
        ROVThruster {
            objectName: "t1";
            orientation: "horizontal";
            rotation: 23;
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t2";
            orientation: "horizontal";
            rotation: -23;
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t3";
            orientation: "horizontal";
            rotation: 157;
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t4";
            orientation: "horizontal";
            rotation: 203;
            value: qsTr("N/A")
        }

    }

    Grid {
        id: grid2
        width: 252
        height: 252
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
        columns: 2
        rows: 2
        spacing: 12
        ROVThruster {
            objectName: "t5";
            orientation: "vertical";
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t6";
            orientation: "vertical";
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t7";
            orientation: "vertical";
            value: qsTr("N/A")
        }
        ROVThruster {
            objectName: "t8";
            orientation: "vertical";
            value: qsTr("N/A")
        }
    }

}
