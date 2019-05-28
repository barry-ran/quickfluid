import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10
import QtQuick.Window 2.10

import Fluid.Controls 1.0 as FluidControls
import FramelessWindowHelper 1.0

FluidControls.ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    //maximumHeight: 680
    minimumWidth: 640
    //maximumWidth: 840
    title: qsTr("Hello World")
    id: root

    Material.theme: Material.Dark
    font.family: "微软雅黑"

    MouseArea {
        anchors.fill: parent
        property point pressPos
        onPressed: pressPos = Qt.point(mouse.x, mouse.y)
        onPositionChanged: {
            if (root.visibility === Window.Windowed) {
                root.x += mouse.x - pressPos.x
                root.y += mouse.y - pressPos.y
            }
        }
        // onDoubleClicked: maxButton.clicked()
    }
    FramelessWindowHelper {

    }

    initialPage: FluidControls.TabbedPage {
        title: qsTr("Tabbed Page")

        actions: [
            FluidControls.Action {
                icon.source: FluidControls.Utils.iconUrl("content/add")
                text: qsTr("Add content")
                toolTip: qsTr("Add content")
                onTriggered: console.log("Example action...")
            }
        ]

        FluidControls.Tab {
            title: qsTr("First")

            Column {
                anchors.centerIn: parent

                Label {
                    text: qsTr("First page")
                }

                Button {
                    text: qsTr("Small")                    
                    icon.source: FluidControls.Utils.iconUrl("content/undo")
                    icon.color: Material.accent                    
                }
                Button {
                    text: qsTr("Medium")
                    highlighted: true
                    Material.background: Material.Teal
                }
                Button {
                    text: qsTr("Large")
                    Material.elevation: 6
                }                
            }
        }

        FluidControls.Tab {
            title: qsTr("Second")

            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }
}
