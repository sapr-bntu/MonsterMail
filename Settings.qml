import QtQuick 1.1

Rectangle {
    width: form.width
    height: form.height
    color: "mediumseagreen"
    Column {
        id: column
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 25
        anchors.left: parent.left
        anchors.leftMargin: 30
        TextInputDesu {
            id: textInputLogin
            objectName: "InputLineLogin"
            fontSize: 24
            width: 400
            widthInputLine: 270
            textLabel: "Login"
            text: "testacc111@open.by"
        }
        TextInputDesu {
            id: textInputFrom
            objectName: "InputLineFrom"
            textLabel: "Proxy"
            width: 400
            widthInputLine: 270
            fontSize: 24
            text: "172.16.110.60:2527"
        }

        TextInputDesu {
            id: textInputServer
            objectName: "InputLineServer"
            fontSize: 24
            width: 400
            widthInputLine: 270
            textLabel: "Server"
            text: "mail.open.by"
        }
        TextInputDesu {
            id: textInputPassword
            objectName: "InputLinePassword"
            fontSize: 24
            width: 400
            widthInputLine: 270
            textLabel: "Password"
            text: "123456"
        }
    }
    Row {
        id: rowButtons
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        height: 40
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
            text: "\uF00C  Save"
            onClicked: {
            }
        }
    }
}
