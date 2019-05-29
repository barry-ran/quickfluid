import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Material 2.10
import QtQuick.Window 2.10
import QtGraphicalEffects 1.0

import Fluid.Controls 1.0 as FluidControls
import FramelessWindowHelper 1.0

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

    }

    UIBase.DragMoveBar {
        id: moveBar
        x: 0
        y: 0
        width: parent.width
        height: 50

        destWindow: root
        onDoubleClicked: root.visibility = Window.Maximized
    }


    DropShadow {
        anchors.fill: mainContent
        horizontalOffset: 1
        verticalOffset: 1
        radius: moveBar.pressed ? 10 : 8
        samples: 10
        source: mainContent
        color: "black"
        Behavior on radius { PropertyAnimation { duration: 100 } }
    }

/*
    Window {
        id: main
        visible: true
        width: 300
        height: 200
        color: "#00000000"
        FramelessWindowHelper {}

        Rectangle {
          id: rect
          color: "red"
          anchors.fill: parent
        }

        DropShadow {
          anchors.fill: rect
          horizontalOffset: 2
          verticalOffset: 2
          radius: 5
          samples: 5
          source: rect
          color: "black"
        }
    }
    */
}
