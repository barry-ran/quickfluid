import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10
import QtQuick.Window 2.10
import QtGraphicalEffects 1.0

import Fluid.Controls 1.0 as FluidControls
import FramelessWindowHelper 1.0
//import SampleApp 1.0

import "./uibase" as UIBase

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#00000000"

    Material.theme: Material.Dark
    font.family: "微软雅黑"

    FramelessWindowHelper {}    

    Page {
        id: mainContent
        anchors.fill: parent
        anchors.margins: (root.visibility === Window.FullScreen || root.visibility === Window.Maximized) ? 0 : 10

        UIBase.DragMoveBar {
            id: moveBar
            x: 0
            y: 0
            width: parent.width
            height: 50

            destWindow: root
            onDoubleClicked: root.visibility = Window.Maximized
        }

        Button {
            id: closeBtn
            width: 50
            height: 50
            //icon.source: FluidControls.Utils.iconUrl("navigation/close")
            icon.source: FluidControls.Utils.iconUrl("action/minimize")
            icon.color: hovered ? "#FF5439" : "#FFFFFF"
            icon.width: width
            icon.height: height

            background: Rectangle {
                opacity: 0
            }
            onClicked: root.close()
        }

    }    

    UIBase.ControlShadow {
        destControl: mainContent
        pressed: moveBar.pressed
    }

    Window {
        id: main
        visible: true
        width: 300
        height: 200
        color: "#00000000"
        FramelessWindowHelper {}

        UIBase.ControlShadow {
            destControl: rect
            pressed: moveBar2.pressed
        }

        UIBase.DragMoveBar {
            id: moveBar2
            x: 0
            y: 0
            width: parent.width
            height: 50

            destWindow: main
            onDoubleClicked: main.visibility = Window.Maximized
        }

        Rectangle {
          id: rect
          color: "red"
          anchors.fill: parent
        }        
    }    
}

/*
BorderlessWindow {
    width: 400
    height: 400
    visible: true
    color: "aqua"

    Rectangle {
        x: 0 // Position 0,0 should be the very top-left of the window, but its not.
        y: 0
        width: parent.width
        height: 20
        color: "purple"
    }
}
*/
