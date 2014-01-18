import QtQuick 1.1


Row{
    id: par
    property alias textLabel: textout.text
    property alias text: textinput.text
    property alias fontSize: textinput.font.pixelSize
    property alias  widthInputLine: inputStringServer.width
    width: 280
    height:fontSize+10
    //color: "mediumseagreen"

    InputDescription
    {
        id:textout;
        TextInput
        {
            id: textinput
        }
    }

    Input
    {
        id: inputStringServer //Имя строки ввода
    }

}
