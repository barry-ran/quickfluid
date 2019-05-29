import QtQuick 2.0
import QtGraphicalEffects 1.0

DropShadow {
    property var destControl
    property bool pressed: false

    anchors.fill: destControl
    horizontalOffset: 1
    verticalOffset: 1
    radius: pressed ? 10 : 8
    samples: 10
    source: destControl
    color: "black"
    Behavior on radius { PropertyAnimation { duration: 100 } }
}
