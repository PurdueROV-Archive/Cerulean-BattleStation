import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

Window {
    property var rovName: c_battlestation.rovName
    property var startTime: 0
    property var delta: 0;
    visible: true
    width: 1910
    height: 1010
    color: "#111111"
    title: "Purdue IEEE | " + c_battlestation.rovName
    objectName: "mainWindow"

    Item {
        objectName: "mainGrid"
        id: mainGrid
        x: 5
        y: 5
        width: 1900
        height: 1000
        transformOrigin: Item.TopLeft
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 27
        anchors.topMargin: 13
        anchors.fill: parent

        Text {
            id: mainTitle
            width: parent.width
            height: titleArea.height
            color: "#805f92dd"
            text: "PURDUE ROV: BATTLESTATION"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.italic: false
            clip: false
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 46
        }

        Column {

            id: column1
            x: 0
            y: 54
            objectName: "column1"
            width: mainGrid.width/3
            height: mainGrid.height-mainTitle.height
            spacing: 20


            ROVBox {
                id: timerArea
                width: column1.width-20
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


//                    Timer {
//                        id: timerTrigger
//                        interval:500; running:false; repeat: true;
//                        onTriggered: {
//                            var tempTime = Math.floor(((new Date).getTime() - startTime)/1000);
//                            var secs = (tempTime % 60);
//                            var mins = Math.floor(tempTime/60);
//                            if(secs < 10) {
//                                secs = "0" + secs;
//                            }
//                            if(mins < 10) {
//                                mins = "0" + mins;
//                            }
//                            timer.text =  mins + ":" + secs;
//                        }
//                    }



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
                id: missionTasks
                width: column1.width - 20
                height: column1.height -20 - timerArea.height
                y: (column1.height/2) - 5
                Text {
                    id: missionTasksTitle
                    x: 117
                    color: "#24487f"
                    text: "MISSION TASKS"
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
                    id: missionTasksTitleInfo
                    x: 0
                    y: 0
                    color: "#ffffff"
                    text: qsTr("MISSION TASK DETAILS")
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
            x: column1.width
            y:54
            width: mainGrid.width/3
            height: mainGrid.height-mainTitle.height
            spacing: 20



            ROVBox {
                id: sysViewArea
                y: 0
                width: column2.width - 20
                height: (column2.height/2) -10
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
                id: sysConfig
                width: column2.width - 20
                height: (column2.height/2) -10
                y: (column2.height/2) - 5
                Text {
                    id: statusTitle
                    x: 117
                    color: "#24487f"
                    text: "ORIENTATION"
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
                    text: qsTr("3D Model Showing ROV Orientation")
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


            id: column3
            objectName: "column3"
            x: column1.width + column2.width
            y:54
            width: mainGrid.width/3
            height: mainGrid.height-mainTitle.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            spacing: 20

            ROVBox {
                id: sysStatus
                y: 0
                width: column3.width - 20
                height: (column3.height/2) -10
                Text {
                    id: sysStatusTitle
                    x: 117
                    color: "#24487f"
                    text: "SYSTEM STATUS"
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
                        anchors.rightMargin: 8
                        anchors.bottomMargin: 40
                             anchors.leftMargin: -8
                             anchors.topMargin: -39
                             anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                             //onClicked handles valid mouse button clicks
                             onClicked: c_inputHandler.setJoystick(1)
                         }
                }
            }
            
            ROVBox {
                id: orientation
                width: column3.width - 20
                height: (column3.height/2) -10
                y: (column3.height/2) - 5
                Text {
                    id: orientationTitle
                    x: 117
                    color: "#24487f"
                    text: "CONFIGURATION"
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
                    id: orienationDetail
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




    }
}
