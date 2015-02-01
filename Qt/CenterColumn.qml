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
    SystemView{}

    //Orientation Status
    Orientation{}

}

