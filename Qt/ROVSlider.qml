import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Slider {

    property string slidercolor
    height: 20
    style: SliderStyle {
        groove: Rectangle {
            implicitWidth: 200
            implicitHeight: 4
            color: slidercolor
            radius: 0
        }
        handle: Rectangle {
            anchors.centerIn: parent
            color: "white"
            implicitHeight: 12
            implicitWidth: 4
        }
    }
}
