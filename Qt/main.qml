import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Window {
    property var rovName: c_battlestation.rovName
    property var startTime: 0
    property var delta: 0;
    visible: true
    width: 1920
    height: 1010
    color: "#111111"
    title: "Purdue IEEE | " + c_battlestation.rovName
    objectName: "mainWindow"

    Item {
        objectName: "mainGrid"
        id: mainGrid
        x: 40
        y: 0
        width: 1900
        height: 900
        clip: false
        transformOrigin: Item.TopLeft
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: -19
        anchors.topMargin: 10
        anchors.fill: parent

        Row{
            id: titleRow
            width: mainGrid.width - 20
            height: 54
            x: 10

            Text {
                id: purdueTitle
                width: parent.width/3
                color: "#e4ae23"
                text: "PURDUE IEEE"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.italic: false
                clip: false
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 28
            }

            Text {
                id: mainTitle
                width: parent.width/3
                height: titleArea.height
                color: "#e4ae23"
                text: "BATTLESTATION"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.italic: false
                clip: false
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 46
            }

            Text {
                id: rovTitle
                width: parent.width/3
                height: titleArea.height
                color: "#e4ae23"
                text: "ROV INCOMPETENCE"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.italic: true
                clip: false
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 28
            }
        }



        Column {

            id: column1
            x: 0
            y: 54
            objectName: "column1"
            width: mainGrid.width/3
            height: mainGrid.height - mainTitle.height - 100
            spacing: 20


            ROVBox {
                id: timerArea
                width: column1.width-20
                height: 110
                x: 10


                Text {
                    id: timerTitle
                    x: 117
                    color: "#e4ae23"
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
                    id: timerBox
                    x: 0
                    y: 0
                    width: timerArea.width
                    height: 70
                    color: "#00000000"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    Row{
                        id: timerRow
                        x: 0
                        y: 0
                        width: timerBox.width
                        height: timerBox.height

                        ROVButton {
                            id: startBtn
                            y: 0
                            height: 70
                            width: 150
                            text: qsTr("START")
                            checkable: false
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            anchors.verticalCenter: parent.verticalCenter
                            MouseArea{
                                id: startButton
                                height: startBtn.height
                                width: startBtn.width
                                anchors.fill: parent
                                onClicked: {
                                    if(timerTrigger.running) {
                                        timerTrigger.stop();
                                        stopResetBtn.enabled = true;
                                        delta = (new Date).getTime() - startTime;
                                        startBtn.text = "RESUME";
                                    } else {
                                        timerTrigger.running = true;
                                        stopResetBtn.enabled = false;
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

                        Text {
                            id: timer
                            y: 0
                            width: 171
                            height: 70
                            text: "00:00"
                            anchors.horizontalCenterOffset: 0
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#e4ae23"
                            font.family: "Arial"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 56
                        }

                        ROVButton {
                            id: stopResetBtn
                            x: 0
                            y: 0
                            height: 70
                            text: qsTr("RESET")
                            enabled: false
                            width: 150
                            anchors.right: parent.right
                            anchors.rightMargin: 30
                            anchors.verticalCenter: parent.verticalCenter
                            MouseArea{
                                id:stopButton
                                height: stopResetBtn.height
                                width: stopResetBtn.width
                                anchors.fill: parent
                                onClicked: {
                                    console.log('Im clicked!');
                                    if(!timerTrigger.running) {
                                        timerTrigger.running = false;
                                        stopResetBtn.enabled = false;
                                        startBtn.text = "START";
                                        timer.text = "00:00";
                                        startTime = 0;
                                    }
                                }
                            }
                             }
                     }
                }
            }

            ROVBox {
                id: missionTasks
                width: column1.width - 20
                height: 800
                x: 10
                y: 130
                Text {
                    id: missionTasksTitle
                    x: 117
                    color: "#e4ae23"
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

                TabView
                {
                    x:10
                    y:30
                    width: missionTasks.width-20
                    height: 550
                    id: missionsTasksTabs

                    style: TabViewStyle {
                          frameOverlap: 1
                          tab: ROVTab {
                              color: styleData.selected ? "#222222" :"#000000"
                              implicitWidth: missionsTasksTabs.width / 3
                              implicitHeight: 50
                              Text {
                                  id: text
                                  anchors.centerIn: parent
                                  text: styleData.title
                                  color: "white"
                                  font.bold: styleData.selected ? true : false
                                  font.pixelSize: 12
                              }
                          }

                          frame: Rectangle {color: "transparent" }
                    }



                    Tab
                    {
                        title: "Science Under the Ice"

                        Column
                        {
                            y: 20
                            spacing: 20

                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "First Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Second Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Third Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fourth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fifth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Sixth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Seventh Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eighth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Ninth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Tenth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eleventh Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Twelfth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Thirteenth Task"
                                    color: "white"
                                    font.pointSize: 14
                                }

                            }

                        }


                    }

                    Tab
                    {
                        title: "Pipeline Inspection & Repair"
                        Column
                        {
                            y: 20
                            spacing: 20
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "First Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Second Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Third Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fourth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fifth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Sixth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Seventh Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eighth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Ninth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Tenth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eleventh Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Twelfth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Thirteenth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fourteenth Task"
                                    font.pointSize: 14
                                }

                            }
                        }

                    }

                    Tab
                    {
                        title: "Oilfield Product. & Maintenance"
                        Column
                        {
                            y: 20
                            spacing: 20
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "First Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Second Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Third Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fourth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Fifth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Sixth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Seventh Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eighth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Ninth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Tenth Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Eleventh Task"
                                    font.pointSize: 14
                                }

                            }
                            CheckBox
                            {
                                x: 10
                                Text
                                {
                                    x: 25
                                    text: "Twelfth Task"
                                    font.pointSize: 14
                                }

                            }

                            }
                        }


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
                x: 10
                width: column2.width - 20
                height: (column2.height/2) -10
                Text {
                    id: sysTitle
                    x: 117
                    width: parent.width
                    color: "#e4ae23"
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
                height: 438
                y: (column2.height/2) - 5
                x: 10
                Text {
                    id: statusTitle
                    x: 117
                    color: "#e4ae23"
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
                x: 10
                width: column3.width - 20
                height: (column3.height/2) -10
                Text {
                    id: sysStatusTitle
                    x: 117
                    color: "#e4ae23"
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
            }
            
            ROVBox {
                id: orientation
                width: column3.width - 20
                height: 438
                y: (column3.height/2) - 5
                x: 10
                Text {
                    id: orientationTitle
                    x: 117
                    color: "#e4ae23"
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
