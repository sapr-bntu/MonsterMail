import QtQuick 1.1

Rectangle {
    color: "mediumseagreen"
    id: rec
    Column {
        id: column
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 15
        Row {
            id: rowToSubj
            spacing: 25
            TextInputDesu {
                id: textInputTo
                objectName: "InputLineTo"
                fontSize: 16
                textLabel: "To"
                text: "testacc111@open.by"
            }
            TextInputDesu {
                id: textInputSubject
                objectName: "InputLineSubject"
                fontSize: 16
                textLabel: "Subject"
                text: ""
                focus: true
            }
        }
        Row {
            id: rowLoginFrom
            spacing: 25
            TextInputDesu {
                id: textInputLogin
                objectName: "InputLineLogin"
                fontSize: 16
                textLabel: "Login"
                text: "testacc111@open.by"
            }
            TextInputDesu {
                id: textInputFrom
                objectName: "InputLineFrom"
                textLabel: "From"
                fontSize: 16
                text: "testacc111@open.by"
            }
        }
        Row {
            id: rowServerPass
            spacing: 25
            TextInputDesu {
                id: textInputServer
                objectName: "InputLineServer"
                fontSize: 16
                textLabel: "Server"
                text: "mail.open.by"
            }
            TextInputDesu {
                id: textInputPassword
                objectName: "InputLinePassword"
                fontSize: 16
                textLabel: "Password"
                text: "123456"
            }
        }
        Rectangle {
            id: mess
            color: "white"
            width: rec.width - 60
            anchors.bottom: rowButtons.top
            anchors.bottomMargin: 15
            anchors.top: rowServerPass.bottom
            anchors.topMargin: 15
            TextEdit {
                id: textinputMessage
                anchors.fill: parent
                objectName: "InputLineBody"
                color: "#151515"
                font.pixelSize: 16
                selectionColor: "blue"
                focus: true
                wrapMode: TextEdit.WordWrap
                text: "Введите текст сообщения"

                font.pointSize: 16
                clip: false
                font.family: "Segoe UI"
            }
        }
        Row {
            id: rowButtons
            height: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            spacing: 25
            Button {
                id: backButton
                text: "\uF177 Back"
                onClicked: {
                    screens.currentIndex = 1
                }
            }
            Button {
                id: sendButton
                text: "\uF112 Send"
                onClicked: {
                    window.sendMessages()
                    screens.currentIndex = 1
                }
            }
        }
    }
}
