import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


Text {
    color: mainColor
    font.family: "Arial"
    font.pixelSize: 20
    font.bold: true
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    width: parent.width-10
    anchors.topMargin: 6
    anchors.top: parent.top
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignTop
    anchors.horizontalCenter: parent.horizontalCenter
}
