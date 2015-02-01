import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Column {
    id: rightColumn
    objectName: "rightColumn"

    width: mainGrid.width/3
    height: mainGrid.height-mainTitle.height
    spacing: 20

    anchors.top: titleRow.bottom
    anchors.right: mainGrid.right
    anchors.rightMargin: 0

    //System Details
    SystemDetails{}

    //Config Details
    ConfigDetails{}
}

