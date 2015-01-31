import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Item{
Text {
    id: purdueTitle
    width: parent.width/3
    height: titleRow.height
    color: mainColor
    text: "PURDUE IEEE"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    font.bold: true
    font.family: "Arial"
    font.pixelSize: 28
}

//Battlestation Title
Text {
    id: mainTitle
    width: parent.width/3
    height: titleRow.height
    color: mainColor
    text: "BATTLESTATION"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.family: "Arial"
    font.pixelSize: 46
}

//ROV Name
Text {
    id: rovTitle
    width: parent.width/3
    height: titleRow.height
    color: mainColor
    text: rovName
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignRight
    font.italic: true
    font.bold: true
    font.family: "Arial"
    font.pixelSize: 28
}
}
