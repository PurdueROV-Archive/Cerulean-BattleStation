import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

Window {
    property var rovName: "ROV PlaceholderName"
    property var startTime: 0
    property var delta: 0;
    visible: true
    width: 1200
    height: 700
    color: "#111111"
    title: "Purdue IEEE | ROV PlaceholderName"
    objectName: "mainWindow"

    Item {
        objectName: "mainGrid"
        id: mainGrid
        transformOrigin: Item.TopLeft
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 30
        anchors.topMargin: 10
        anchors.fill: parent

        Column {
            id: column1
            objectName: "column1"
            width: timerArea.width
            height: 400
            spacing: 20

            Column {
                id: titleArea
                objectName: "titleArea"
                width: title.width
                height: 50

                Text {
                    id: purdueTag
                    objectName: "purdueTag"
                    color: "#24487f"
                    text: qsTr("PURDUE IEEE")
                    transformOrigin: Item.Center
                    font.family: "Arial"
                    font.bold: true
                    font.italic: false
                    font.pixelSize: 14
                }

                Text {
                    id: title
                    color: "#6092dd"
                    text: rovName
                    font.italic: true
                    clip: false
                    font.bold: true
                    font.family: "Arial"
                    font.pixelSize: 28
                }



            }

            ROVBox {
                id: timerArea
                width: 300
                height: 140


                Text {
                    id: timerTitle
                    x: 117
                    color: "#24487f"
                    text: "TIMER"
                    font.family: "Arial"
                    style: Text.Normal
                    textFormat: Text.AutoText
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 6
                    font.pixelSize: 20
                }



                Item{
                    id: item1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 32
                    Text {
                        id: timer
                        text: "00:00"
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "#6092dd"
                        font.family: "Courier"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 56
                    }

                    Timer {
                        id: timerTrigger
                        interval:500; running:false; repeat: true;
                        onTriggered: {
                            var tempTime = Math.floor(((new Date).getTime() - startTime)/1000);
                            var secs = (tempTime % 60);
                            var mins = Math.floor(tempTime/60);
                            if(secs < 10) {
                                secs = "0" + secs;
                            }
                            if(mins < 10) {
                                mins = "0" + mins;
                            }
                            timer.text =  mins + ":" + secs;
                        }
                    }


                }

                Rectangle {
                    id: timerButtonRow
                    x: 143
                    y: 97
                    width: 250
                    height: 36
                    color: "#00000000"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10

                    ROVButton {
                        id: startBtn
                        y: 0
                        text: qsTr("START")
                        checkable: false
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        MouseArea{
                            id: startButton
                            anchors.fill: parent
                            onClicked: {
                                if(timerTrigger.running) {
                                    timerTrigger.stop();
                                    delta = (new Date).getTime() - startTime;
                                    startBtn.text = "RESUME";
                                } else {
                                    timerTrigger.running = true;
                                    startBtn.text = "PAUSE";
                                    if(startTime == 0) {
                                        startTime = (new Date).getTime();
                                    } else {
                                        startTime = (new Date).getTime() - delta;
                                    }
                                }
                            }

                        }
                    }

                    ROVButton {
                        id: stopResetBtn
                        x: 0
                        y: 0
                        text: "RESET"
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        MouseArea{
                            id:stopButton
                            anchors.fill: parent
                            onClicked: {
                                if(!timerTrigger.running) {
                                    timerTrigger.running = false;
                                    startBtn.text = "START";
                                    timer.text = "00:00";
                                    startTime = 0;
                                }
                            }
                        }
                    }
                }
            }

            ROVBox {
                id: networkStatusArea
                width: 300
                height: 140
                Text {
                    id: netStatTitle
                    x: 117
                    color: "#24487f"
                    text: "NETWORK"
                    anchors.topMargin: 6
                    anchors.top: parent.top
                    style: Text.Normal
                    textFormat: Text.AutoText
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Arial"
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                }

                Item {
                    id: netStatContent
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 32
                    anchors.fill: parent

                    Item {
                        id: dROBox
                        x: 81
                        width: 96
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.top: parent.top

                        Label {
                            id: dROTitle
                            x: 38
                            color: "#24487f"
                            text: qsTr("OUT")
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 8
                            font.bold: true
                            font.pointSize: 12
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Label {
                            id: dROVal
                            x: 0
                            color: "#6092dd"
                            text: "88"
                            anchors.top: parent.top
                            anchors.topMargin: 24
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                            font.pointSize: 42
                            font.family: "Courier"
                        }

                        Label {
                            id: dROUnit
                            x: 0
                            y: 0
                            color: "#24487f"
                            text: "kbps"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 12
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pointSize: 10
                            font.bold: true
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    Item {
                        id: dRIBox
                        x: 87
                        y: 0
                        width: 96
                        anchors.bottom: parent.bottom
                        anchors.top: parent.top
                        Label {
                            id: dRITitle
                            x: 38
                            color: "#24487f"
                            text: qsTr("IN")
                            font.pointSize: 12
                            anchors.topMargin: 8
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                        }

                        Label {
                            id: dRIVal
                            x: 0
                            color: "#6092dd"
                            text: "88"
                            font.pointSize: 42
                            anchors.topMargin: 24
                            anchors.top: parent.top
                            font.family: "Courier"
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                        }

                        Label {
                            id: dRIUnit
                            x: 0
                            y: 0
                            color: "#24487f"
                            text: "kbps"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 12
                            font.pointSize: 10
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                        }
                        anchors.right: parent.right
                        anchors.rightMargin: 96
                    }

                    Item {
                        id: netStatus
                        y: 0
                        width: 88
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.top: parent.top

                        Label {
                            id: netStatusTitle
                            x: 32
                            color: "#24487f"
                            text: qsTr("STATUS")
                            anchors.top: parent.top
                            anchors.topMargin: 8
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pointSize: 12
                            font.bold: true
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Label {
                            id: dRIVal1
                            x: 0
                            color: "#17b804"
                            text: "OK"
                            anchors.verticalCenter: parent.verticalCenter
                            font.pointSize: 24
                            font.family: "Arial"
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                        }
                    }
                }
            }

            ROVBox {
                id: powerArea
                width: 300
                height: 270
                Text {
                    id: powerTitle
                    x: 117
                    color: "#24487f"
                    text: "POWER"
                    anchors.topMargin: 6
                    anchors.top: parent.top
                    style: Text.Normal
                    textFormat: Text.AutoText
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Arial"
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                }

                Text {
                    id: powerPlaceholder
                    x: 0
                    y: 0
                    color: "#ffffff"
                    text: qsTr("VOLTAGE, POWER DRAW, ETC")
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }








        }

        Column {
            id: column2
            x: column1.width + 20
            width: sysStatusArea.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: titleArea.height + 20
            anchors.top: parent.top

            ROVBox {
                id: sysStatusArea
                y: 0
                width: 300
                height: column2.height
                Text {
                    id: sysStatusTitle
                    x: 117
                    color: "#24487f"
                    text: "SYSTEMS"
                    anchors.topMargin: 6
                    anchors.top: parent.top
                    font.pixelSize: 20
                    textFormat: Text.AutoText
                    style: Text.Normal
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    font.family: "Arial"
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                }

                Text {
                    id: sysStatusPlaceholder
                    x: 0
                    y: 0
                    width: parent.width
                    color: "#ffffff"
                    text: qsTr("SYSTEM DETAILS  (MOTORS, ACTUATORS, ETC) AND TOGGLES/CONTROLS")
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                ROVButton {
                    id: fireMissiles
                    x: 94
                    y: 324
                    width: parent.width - 40
                    text: "FIRE MISSILES"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    MouseArea{
                             id: fireMissilesArea
                             anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                                     //onClicked handles valid mouse button clicks
                             //onClicked: testFunction("BUTTON HATH BEEN PRESSED MISSILES AWAY")
                         }
                }
            }


        }

        Column {
            id: column3
            x: 0
            width: 540
            height: mainGrid.height - titleArea.height - 20
            anchors.right: parent.right
            anchors.rightMargin: 0
            spacing: 20

            Text {
                id: title1
                width: parent.width
                height: titleArea.height
                color: "#805f92dd"
                text: "BATTLESTATION //"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.italic: false
                clip: false
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 46
            }

            ROVBox {
                id: sysViewArea
                y: 0
                width: parent.width
                height: 380
                Text {
                    id: sysTitle
                    x: 117
                    width: parent.width
                    color: "#24487f"
                    text: "SYSTEM VIEW"
                    anchors.topMargin: 6
                    anchors.top: parent.top
                    style: Text.Normal
                    textFormat: Text.AutoText
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Arial"
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                }

                Text {
                    id: sysPlaceholder
                    x: 0
                    y: 0
                    color: "#ffffff"
                    text: qsTr("BOT DIAGRAM AND OTHER VISUAL THINGS")
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                }
            }

            ROVBox {
                id: configArea
                y: 0
                width: parent.width
                height: 190
                Text {
                    id: configTitle
                    x: 117
                    width: parent.width
                    color: "#24487f"
                    text: "CONFIGURATION"
                    anchors.topMargin: 6
                    anchors.top: parent.top
                    font.pixelSize: 20
                    textFormat: Text.AutoText
                    style: Text.Normal
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    font.family: "Arial"
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                }

                Text {
                    id: configPlaceholder
                    x: 0
                    y: 0
                    color: "#ffffff"
                    text: qsTr("CONFIGURATION DETAILS")
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ROVComboBox {
                    id: comboBox
                    x: 94
                    y: 324
                    width: parent.width - 40
                    activeFocusOnPress: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                }
            }

        }



    }
}
