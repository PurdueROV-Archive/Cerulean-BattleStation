import QtQuick 2.2

ROVBox {
    id: sysStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysStatusTitle
        text: "SYSTEM STATUS"
    }

    Text {
        id: sysStatusDetails
        width: parent.width - 10
        color: "white"
        text: qsTr("SYSTEM DETAILS  (MOTORS, ACTUATORS, ETC) AND TOGGLES/CONTROLS")
        wrapMode: Text.WordWrap
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    //                ComboBox {
    //                    objectName: "serialSelection"
    //                    width: 200
    //                    model: c_inputHandler.joysticks
    //                }

}
