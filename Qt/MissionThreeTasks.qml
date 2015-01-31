import QtQuick 2.2

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
