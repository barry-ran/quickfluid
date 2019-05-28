import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10
import QtQuick.Window 2.10

import Fluid.Controls 1.0 as FluidControls
import FramelessWindowHelper 1.0

import "./uibase" as UIBase

FluidControls.ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    //maximumHeight: 680
    minimumWidth: 640
    //maximumWidth: 840
    id: root

    Material.theme: Material.Dark
    font.family: "微软雅黑"

    FramelessWindowHelper {}

    UIBase.DragMoveBar {
        x: 0
        y: 0
        width: parent.width
        height: 50

        destWindow: root
        onDoubleClicked: root.visibility = Window.Maximized
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
    }
}
