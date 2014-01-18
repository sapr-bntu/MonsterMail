import QtQuick 1.1

Rectangle {
    id: button
    border.color: "white"
    border.width: 2
    width: textout.width + 10;
    radius: 0
    height: 40

    FontLoader {
        id: segoe
        source: "segoe.ttf"
    }
    FontLoader {
        id: awesome
        source: "awesome.ttf"
    }
    FontLoader {
        id: helvetica
        source: "helvetica.ttf"
    }

    property alias text: textout.text

    signal clicked

    anchors.margins: 10
    color: "mediumseagreen"

    Text {
        id: textout
        color: "white"
        font.pixelSize: 26
        font.family: "FontAwesome"
        anchors.centerIn: parent;
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: button.clicked()
        onPressed: {
            textout.color = "seagreen"
            button.border.color = "white"
            button.color = "white"
        }
        onReleased: {
            textout.color = "white"
            button.border.color = "white"
            button.color = "mediumseagreen"
        }

        hoverEnabled: true
    }
}
