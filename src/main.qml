import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10
import QtQuick.Window 2.10

import Fluid.Controls 1.0 as FluidControls
import FramelessWindowHelper 1.0

import "./uibase" as UIBase

ApplicationWindow {
    id: root

    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    //maximumHeight: 680
    minimumWidth: 640
    //maximumWidth: 840

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
}
