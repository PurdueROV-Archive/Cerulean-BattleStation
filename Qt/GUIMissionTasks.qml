import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

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
