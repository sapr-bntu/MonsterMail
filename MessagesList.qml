import QtQuick 1.1

Rectangle {
    color: "white"
    anchors.top: parent.top

    ListView {
        id: treeView
        anchors.fill: parent
        //Задаем делегата
        delegate: treeDelegate
        //Задаем модель, этот объект позже придет из C++
        model: treeModel
        clip: true

        //Компонент делегата
        Component {
            id: treeDelegate
            Item {
                id: component
                height: 50
                width: treeView.width
                Rectangle {
                    anchors.fill: parent
                    id: message
                    color: mouse_area_message.containsMouse?"mediumseagreen": "white"
                    //Полоска для отделения элементов друг от друга
                    Rectangle {
                        height: 1
                        anchors.top: parent.top
                        width: parent.width - 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }

                    //Область для отображения данных элемента
                    Text {
                        id: nameTextElement
                        text: name
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.Center
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                    }
                    Rectangle {
                        height: 1
                        anchors.top: parent.bottom
                        width: parent.width - 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }
                    MouseArea {
                        id: mouse_area_message
                        anchors.fill: parent
                        onClicked: {
                            console.log("Component clicked",index," ",dirs.currentIndex)
                            window.showMessage(index,dirs.currentIndex)
                        }
                        onReleased: {
                            message.color = "silver"
                        }


                        hoverEnabled: true
                    }
                }
            }
        }
    }

    ListModel {
        id: treeModel
        objectName: "treeModel"
    }
    function clear() {
        console.log("qml clear")
        treeModel.clear()
    }
    function append(newElement) {
        console.log("qml append")
        treeModel.insert(0, {
                             name: newElement
                         })
    }
}
