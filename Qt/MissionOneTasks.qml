import QtQuick 2.0

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
