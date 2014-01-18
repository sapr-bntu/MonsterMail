import QtQuick 1.1

Rectangle {
    width: form.width
    height: form.height
    color: "white"

    Column {
        anchors.fill: parent
        id: layout
        Row {
            spacing: 10
            Column {
                id: sidebar
                height: form.height - menu.height
                width: 200

                    Directory {
                        width: parent.width
                        height: 50
                        id: dirs

                    }
                    MessagesList {
                        id: messages
                        width: parent.width
                        height: parent.height - dirs.height
                        anchors.top: dirs.bottom
                        anchors.bottom: menu.top
                        objectName: "messages"
                    }

            }
            Rectangle {
                anchors.leftMargin: 10
                anchors.topMargin: 10
                anchors.left: sidebar.right
                width: layout.width - sidebar.width
                height: sidebar.height
                MessageView {
                    anchors.fill: parent
                    id: message
                    objectName: "message"
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 70
            color: "mediumseagreen"
            Row {
                id: menu
                anchors.margins: 15
                spacing: 10
                height: 70

                CircleButton {
                    id: recieveButton
                }

                CircleButton {
                    id: sendButton
                    labelText: "Send"
                    iconText: "\uF062"
                    desu: 2
                }

                CircleButton {
                    id: settingsButton
                    iconText: "\uF013"
                    labelText: "Settings"
                    desu: 0
                }
            }
        }
    }
}
