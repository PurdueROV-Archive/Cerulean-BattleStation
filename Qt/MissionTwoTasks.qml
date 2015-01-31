import QtQuick 2.2

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

