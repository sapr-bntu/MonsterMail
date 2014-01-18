import QtQuick 1.1

Rectangle {
    anchors.right: par.right
    //Размещаем ниже
    height: fontSize+12;
    width: 200
    TextInput {
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        id: textinput
        objectName: "textinput"
        color: "black";
        font.pixelSize: fontSize;
        selectionColor: "blue"
        focus: false
        }
}
