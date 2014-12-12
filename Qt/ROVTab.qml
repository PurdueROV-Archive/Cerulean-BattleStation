import QtQuick 2.0
import QtGraphicalEffects 1.0


Rectangle {

    Rectangle {
        id: rovTab
        color: "#00000000"
        radius: 0
        border.color: mainColor
        border.width: 1
        width: parent.width
        height: parent.height
    }


    Glow {
        anchors.fill: rovTab
        radius: styleData.selected ? 12 : 0
        samples: 16
        color: mainColor
        source: rovTab
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: styleData.title
        color: "white"
        font.bold: styleData.selected
        font.pixelSize: 12
    }
}
