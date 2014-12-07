import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    color: "#00000000"
    Rectangle {
        id: rovRectangle
        color: "#00000000"
        radius: 0
        border.color: "#b1946c"
        border.width: 1
        width: parent.width
        height: parent.height
    }
    Glow {
        anchors.fill: rovRectangle
        radius: 12
        samples: 16
        color: "#b1946c"
        source: rovRectangle
    }
}
