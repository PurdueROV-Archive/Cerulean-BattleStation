import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: configuration
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    ROVTitle {
        id: configurationTitle
        text: "CONFIGURATION"
    }

    TabView {
        id: configurationTab
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: configurationTitle.bottom
        width: parent.width-30
        height: parent.height
        clip: true

        style: TabViewStyle {
            frameOverlap: 1
            tab: ROVTab {
                color: styleData.selected ? "#222222" :"#000000"
                clip: true
                implicitWidth: (configurationTab.width)/3
                implicitHeight: 50
            }

            frame: Rectangle {color: "transparent" }
        }

        //Configuration 1
        Tab {
            id: tab1
            title: "Speed Control"

            Column {
                id: speedcontrol
                spacing: 10
                y: 20

                ROVSlider {
                    labeltext: "Horizontal Speed Control: "
                    objectName: "horizontalSlider"
                }

                ROVSlider {
                    labeltext: "Vertical Speed Control:"
                    objectName: "verticalSlider"
                }

                ROVSlider {
                    labeltext: "Strafe Speed Control:"
                    objectName: "strafeSlider"
                }

                ROVSlider {
                    labeltext: "Pitch/Roll Speed Control:"
                    objectName: "pitchRollSlider"
                }
            }
        }

        //Configuration 2
        Tab {

            title: "Serial and Controller"

            Flickable {
                width: parent.width
                height: parent.height
                flickableDirection: Flickable.VerticalFlick
                contentHeight: configsettings2.height+80
                contentWidth: configsettings2.width
                boundsBehavior: Flickable.StopAtBounds

                Column {
                    id: configsettings2
                    y: 20
                    spacing: 20
                }
            }
        }

        //Configuration 3
        Tab {
            title: "Configuration 3"

            Flickable {
                width: parent.width
                height: parent.height
                flickableDirection: Flickable.VerticalFlick
                contentHeight: configsettings3.height+80
                contentWidth: configsettings3.width
                boundsBehavior: Flickable.StopAtBounds

                Column {
                    id: configsettings3
                    y: 20
                    spacing: 20

                }
            }
        }
    }
}
