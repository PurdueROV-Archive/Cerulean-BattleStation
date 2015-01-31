import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

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
    GUITimer{
        id: timerArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        height: 110

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
                MissionOneTasks{}
            }

            //Mission 2 Tasks
            Tab {
                title: "Pipeline Inspection & Repair"
                MissionTwoTasks{}
            }

            //Mission 3 Tasks
            Tab {
                title: "Oilfield Prod & Maintenance"
                MissionThreeTasks{}
            }
        }
    }
}

