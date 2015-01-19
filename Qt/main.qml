import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Window {
    property string rovName: c_battlestation.rovName
    property var startTime: 0
    property var delta: 0;
    property string mainColor: "#e4ae23"
    visible: true
    width: 1920
    height: 1010
    visibility: "Maximized"
    color: "#111111"
    title: "Purdue IEEE | " + c_battlestation.rovName
    objectName: "mainWindow"

    Item {
        objectName: "mainGrid"
        id: mainGrid
        width: parent.height
        height: parent.width
        clip: true
        transformOrigin: Item.TopLeft
        anchors.margins: 10
        anchors.bottomMargin: 20
        anchors.fill: parent

        //Titles
        Row {
            id: titleRow
            width: mainGrid.width - 40
            height: 60
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            //Purdue IEEE
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


        //Left Column
        Column {
            id: leftColumn
            objectName: "leftColumn"

            width: mainGrid.width/3
            height: mainGrid.height - mainTitle.height
            spacing: 20

            anchors.top: titleRow.bottom
            anchors.left: mainGrid.left
            anchors.leftMargin: 0

            //Timer Container
            ROVBox {
                id: timerArea
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: 110


                //Timer Title
                ROVTitle {
                    id: timerTitle
                    text: "TIMER"
                }

                //Timer
                Timer {
                    id: timerTrigger
                    interval:500; running:false; repeat: true;
                    onTriggered: {
                        var tempTime = Math.floor(((new Date).getTime() - startTime)/1000);
                        var secs = (tempTime % 60);
                        var mins = Math.floor(tempTime/60);

                        secs = secs < 10 ? secs = "0" + secs : secs;
                        mins = mins < 10 ? mins = "0" + mins : mins;

                        timer.text =  mins + ":" + secs;
                    }
                }

                //Holder for buttons and text
                Item {
                    id: timerRow
                    anchors.top: timerTitle.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10


                    //Start button
                    ROVButton {
                        id: startBtn
                        height: 70
                        width: 150
                        text: qsTr("START")
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        enabled: true
                        MouseArea {
                            id: startButton
                            height: startBtn.height
                            width: startBtn.width
                            anchors.fill: parent
                            onClicked: {
                                if (timerTrigger.running) {
                                    timerTrigger.stop();
                                    stopResetBtn.enabled = true;
                                    delta = (new Date).getTime() - startTime;
                                    startBtn.text = "RESUME";
                                } else {
                                    timerTrigger.running = true;
                                    stopResetBtn.enabled = false;
                                    startBtn.text = "PAUSE";
                                    if (startTime == 0) {
                                        startTime = (new Date).getTime();
                                    } else {
                                        startTime = (new Date).getTime() - delta;
                                    }
                                }
                            }
                        }
                    }

                    //Stop button
                    ROVButton {
                        id: stopResetBtn
                        height: 70
                        width: 150
                        text: qsTr("RESET")
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        enabled: false
                        MouseArea {
                            id:stopButton
                            height: stopResetBtn.height
                            width: stopResetBtn.width
                            anchors.fill: parent
                            onClicked: {
                                if (!timerTrigger.running) {
                                    timerTrigger.running = false;
                                    stopResetBtn.enabled = false;
                                    startBtn.text = "START";
                                    timer.text = "00:00";
                                    startTime = 0;
                                }
                            }
                        }
                    }

                    //Timer text
                    Text {
                        id: timer
                        y: 0
                        width: 171
                        height: 70
                        text: "00:00"
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenterOffset: 0

                        color: mainColor
                        font.family: "Arial"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 56
                    }
                }
            }


            //Mission Tasks
            ROVBox {
                id: missionTasks
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: parent.height - timerArea.height-20

                ROVTitle {
                    id: missionTasksTitle
                    text: "MISSION TASKS"
                }

                TabView {
                    id: missionTasksTab
                    anchors.top: missionTasksTitle.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width-30
                    height: parent.height
                    clip: true

                    style: TabViewStyle {
                        frameOverlap: 1
                        tab: ROVTab {
                            color: styleData.selected ? "#222222" :"#000000"
                            clip: true
                            implicitWidth: (missionTasksTab.width)/3
                            implicitHeight: 50
                        }

                        frame: Rectangle {color: "transparent" }
                    }

                    //Mission 1 Tasks
                    Tab {
                        title: "Science Under the Ice"

                        Flickable {
                            width: parent.width
                            height: parent.height
                            flickableDirection: Flickable.VerticalFlick
                            contentHeight: mission1tasks.height+80
                            contentWidth: mission1tasks.width
                            boundsBehavior: Flickable.StopAtBounds

                            Column {
                                id: mission1tasks
                                width: parent.width
                                y: 20
                                spacing: 20

                                ROVMissionTask {
                                    text: "Return algae sample - 5pts"
                                }
                                ROVMissionTask {
                                    text: "Remove sea urchin - 5pts"
                                }
                                ROVMissionTask {
                                    text: "Return sea urchin - 5pts"
                                }
                                ROVMissionTask {
                                    text: "Count and identify star species - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Deploy acoustic sensor - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Survey iceberg at 4 points - 5pts"
                                }
                                ROVMissionTask {
                                    text: "Measure iceberg keel depth - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Measure iceberg diameter - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Calculate iceberg volume - 5pts"
                                }
                                ROVMissionTask {
                                    text: "Map location of iceberg from coordinates - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Determine iceberg threat to surface platforms - 10pts"
                                }
                                ROVMissionTask {
                                    text: "Determine iceberg threat to subsea assets - 10pts"
                                }

                            }
                        }
                    }

                    //Mission 2 Tasks
                    Tab {
                        title: "Pipeline Inspection & Repair"

                        Flickable {
                            width: parent.width
                            height: parent.height
                            flickableDirection: Flickable.VerticalFlick
                            contentHeight: mission2tasks.height+80
                            contentWidth: mission2tasks.width
                            boundsBehavior: Flickable.StopAtBounds

                            Column {
                            id: mission2tasks
                            y: 20
                            spacing: 20

                            ROVMissionTask {
                                text: "Find corroded pipe section - 5pts"
                            }
                            ROVMissionTask {
                                text: "Turn valve to stop oil flow - 10pts"
                            }
                            ROVMissionTask {
                                text: "Verify gauge pressure is zero - 5pts"
                            }
                            ROVMissionTask {
                                text: "Measure corroded pipe section - 10pts"
                            }
                            ROVMissionTask {
                                text: "Attach lift line to corroded section - 10pts"
                            }
                            ROVMissionTask {
                                text: "Pull pins to cut corroded section (2 sections) - 10pts"
                            }
                            ROVMissionTask {
                                text: "Remove corroded pipe to surface - 5pts"
                            }
                            ROVMissionTask {
                                text: "Install flange adapter (2 installations) - 10pts"
                            }
                            ROVMissionTask {
                                text: "Insert bolts to secure flanges (2 flanges) - 10pts"
                            }
                            ROVMissionTask {
                                text: "Remove wellhead cover - 5pts"
                            }
                            ROVMissionTask {
                                text: "Install wellhead gasket - 5pts"
                            }
                            ROVMissionTask {
                                text: "Replace wellhead cover - 5pts"
                            }
                            ROVMissionTask {
                                text: "Insert hot stab into wellhead port - 5pts"
                            }
                            ROVMissionTask {
                                text: "Remove hot stab and return to surface - 5pts"
                            }
                        }
                        }
                    }

                    //Mission 3 Tasks
                    Tab {
                        title: "Oilfield Prod & Maintenance"

                        Flickable {
                            width: parent.width
                            height: parent.height
                            flickableDirection: Flickable.VerticalFlick
                            contentHeight: mission3tasks.height+80
                            contentWidth: mission3tasks.width
                            boundsBehavior: Flickable.StopAtBounds

                            Column {
                            id: mission3tasks
                            y: 20
                            spacing: 20


                            ROVMissionTask {
                                text: "Test first anode - 10pts"
                            }
                            ROVMissionTask {
                                text: "Test second anode - 10pts"
                            }
                            ROVMissionTask {
                                text: "Test third anode - 10pts"
                            }
                            ROVMissionTask {
                                text: "Test fourth anode - 10pts"
                            }
                            ROVMissionTask {
                                text: "Measure wellhead height - 5pts"
                            }
                            ROVMissionTask {
                                text: "Measure wellhead length - 5pts"
                            }
                            ROVMissionTask {
                                text: "Calculate wellhead angle - 5pts"
                            }
                            ROVMissionTask {
                                text: "Evaluate pipeline system oil flow - 5pts"
                            }
                            ROVMissionTask {
                                text: "Open/Close all 6 valves - 10pts"
                            }
                            ROVMissionTask {
                                text: "Move water through pipeway - 20pts"
                            }
                            ROVMissionTask {
                                text: "Determine average flow rate - 10pts"
                            }
                        }

                        }
                    }
                }
            }
        }


        //Center Column
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
            ROVBox {
                id: sysViewArea
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                clip: true

                height: (parent.height/2) - 10

                ROVTitle {
                    id: sysTitle
                    text: "SYSTEM VIEW"
                }

                Grid {
                    id: grid1
                    width: 365
                    height: 365
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    antialiasing: true
                    columns: 2
                    rows: 2
                    spacing: 125
                    ROVThruster {
                        objectName: "t1";
                        orientation: "horizontal";
                        rotation: 23;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t2";
                        orientation: "horizontal";
                        rotation: -23;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t3";
                        orientation: "horizontal";
                        rotation: 157;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t4";
                        orientation: "horizontal";
                        rotation: 203;
                        value: qsTr("N/A")
                    }

                }

                Grid {
                    id: grid2
                    width: 252
                    height: 252
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    antialiasing: true
                    columns: 2
                    rows: 2
                    spacing: 12
                    ROVThruster {
                        objectName: "t5";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t6";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t7";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t8";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                }

            }

            //Orientation Status
            ROVBox {
                id: orientationStatus
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: (parent.height/2) - 10

                ROVTitle {
                    id: orientationTitle
                    text: "ORIENTATION"
                }

                Text {
                    id: orientationDetail
                    width: parent.width - 10
                    color: "white"
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

        //Right Column
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
            ROVBox {
                id: sysStatus
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: (parent.height/2) - 10

                ROVTitle {
                    id: sysStatusTitle
                    text: "SYSTEM STATUS"
                }

                Text {
                    id: sysStatusDetails
                    width: parent.width - 10
                    color: "white"
                    text: qsTr("SYSTEM DETAILS  (MOTORS, ACTUATORS, ETC) AND TOGGLES/CONTROLS")
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

//                ComboBox {
//                    objectName: "serialSelection"
//                    width: 200
//                    model: c_inputHandler.joysticks
//                }

            }
            
            //Config Details
            ROVBox {
                id: config
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: (parent.height/2) - 10

                ROVTitle {
                    id: configTitle
                    text: "CONFIGURATION"
                }

                Column {
                    spacing: 10
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 20
                    anchors.topMargin: 50
                    anchors.top: configTitle.bottom

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
        }
    }
}
