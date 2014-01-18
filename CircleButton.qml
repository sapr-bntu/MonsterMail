import QtQuick 1.1

Rectangle {
    width: text.width + 10
    anchors.verticalCenter: menu.verticalCenter
    height: button.height + text.height
    color: "mediumseagreen"
    property string iconText: "\uF063"
    property string labelText: "Recieve"
    property int desu: 1
    Button {
        id: button
        width: height
        radius: width/2;
        anchors.horizontalCenter: parent.horizontalCenter
        text: parent.iconText
        onClicked: {
            if (desu==1)
            {
                window.receiveMessages()
            }
            else
            {
                screens.currentIndex = desu
            }
        }
    }
    Text {
        id: text
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        font.pixelSize: 14
        font.family: "Segoe UI"
        text: parent.labelText
        anchors.top: button.bottom
    }
}
