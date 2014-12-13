import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: holder
    property string labeltext
    width: parent.width
    height: 50


    Item {
        id: row
        //spacing: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottomMargin: 10

        Text {
            id: labelText
            text: labeltext
            color: "white"
            font.pixelSize: 15
            anchors.left: parent.left
        }

        Text {
            id: valueText
            text: "100%"
            color: "white"
            font.pixelSize: 15
            anchors.right: parent.right
        }
    }

    Slider {
        id: slider
        value: 100
        minimumValue: 0
        maximumValue: 100
        stepSize: 10
        tickmarksEnabled: true
        onValueChanged: updatePos();
        width: parent.width
        anchors.top: row.bottom
        anchors.topMargin: 25


        style: SliderStyle {
            groove: Rectangle {
                implicitHeight: 4
                color: mainColor
                radius: 0
            }

            handle: Rectangle {
                anchors.centerIn: parent
                color: "white"
                implicitHeight: 20
                implicitWidth: 20
                radius: 5
            }
        }

    }


    function updatePos() {
        valueText.text = slider.value + "%";
    }

}
