import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Column {
    id: centerColumn
    objectName: "centerColumn"

    width: mainGrid.width/3
    height: mainGrid.height-mainTitle.height
    spacing: 20

    anchors.top: titleRow.bottom
    anchors.horizontalCenterOffset: 0
    anchors.horizontalCenter: parent.horizontalCenter

    //System View
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

    //Orientation Status
    ROVBox {
        id: orientationStatus
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        height: (parent.height/2) - 10

        ROVTitle {
            id: orientationTitle
            text: "ORIENTATION"
        }

        Text {
            id: orientationDetail
            width: parent.width - 10
            color: "white"
            text: qsTr("3D Model Showing ROV Orientation")
            wrapMode: Text.WordWrap
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

