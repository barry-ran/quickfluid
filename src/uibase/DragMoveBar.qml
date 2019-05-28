import QtQuick 2.10
import QtQuick.Window 2.10

Item {
    id: root

    property alias destWindow: dragMoveBar.destWindow

    signal doubleClicked()

    MouseArea {
        id: dragMoveBar
        property Window destWindow
        property point pressPos
        anchors.fill: parent
        onPressed: pressPos = Qt.point(mouse.x, mouse.y)
        onPositionChanged: {
            if (destWindow.visibility === Window.Windowed) {
                destWindow.x += mouse.x - pressPos.x
                destWindow.y += mouse.y - pressPos.y
            }
        }
        onDoubleClicked: root.doubleClicked()
    }
}

