import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

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
