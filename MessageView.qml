import QtQuick 1.1


Rectangle {
    id: rectangle3
    color: "#ffffff"
    property string text: "Click on necessary to you e-mail and it will be shown here"

    Flickable {
        id: flickArea
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        clip: true
        TextEdit{
            anchors.fill: parent
            id: helpText
            text: rectangle3.text
            font.pointSize: 12
            font.family: "Open Sans"
            wrapMode: TextEdit.WordWrap
            textFormat: TextEdit.AutoText
            readOnly:true
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            clip: true
        }
    }
}
