import QtQuick 2.2

ROVBox {
    id: sysStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    clip: true

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysStatusTitle
        text: "SYSTEM STATUS"
    }

    Flickable {
        width: sysStatus.width
        height: sysStatus.height
        flickableDirection: Flickable.VerticalFlick
        contentHeight: thrusterControl.height+80
        contentWidth: thrusterControl.width
        boundsBehavior: Flickable.StopAtBounds
        clip: true


        Column {
            id: thrusterControl
            width: sysStatus.width-55
            spacing: 10
            y: 20
            clip: true

            ROVSlider {
                labeltext: "Thruster 1:"
                objectName: "t1Control"
            }

            ROVSlider {
                labeltext: "Thruster 2:"
                objectName: "t2Control"
            }

            ROVSlider {
                labeltext: "Thruster 3:"
                objectName: "t3Control"
            }
            ROVSlider {
                labeltext: "Thruster 4:"
                objectName: "t4Control"
            }

            ROVSlider {
                labeltext: "Thruster 5:"
                objectName: "t5Control"
            }

            ROVSlider {
                labeltext: "Thruster 6:"
                objectName: "t6Control"
            }

            ROVSlider {
                labeltext: "Thruster 7:"
                objectName: "t7Control"
            }
            ROVSlider {
                labeltext: "Thruster 8:"
                objectName: "t8Control"
            }
        }
    }

}
