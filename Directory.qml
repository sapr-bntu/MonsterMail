import QtQuick 1.1

Rectangle {
    color: "white"
    height: 70
    border.width: 0
    border.color: "black"
    property int currentIndex: treeView.currentIndex
    ListView {
        id: treeView
        width: parent.width
        height: parent.height
        //Задаем делегата
        delegate: treeDelegate
        //Задаем модель, этот объект позже придет из C++
        model: treeModel
        clip: true
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem
        boundsBehavior: Flickable.DragOverBounds
        highlightRangeMode: ListView.StrictlyEnforceRange
        keyNavigationWraps: true

        onCurrentIndexChanged: {
            window.showDirectory(treeView.currentIndex)
            console.log(treeView.currentIndex)
        }

        //Компонент делегата
        Component {
            id: treeDelegate
            Item {
                id: component
                height: 50
                width: treeView.width

                //Полоска для отделения элементов друг от друга
                Rectangle {
                    height: 1
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width -10
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

                MouseArea {
                    anchors.fill: parent
                    onClicked:  {
                        console.log("Directory component clicked")
                        window.showDirectory(index)
                    }
                }
                Timer {
                    interval: 500; running: true; repeat: false
                    onTriggered: {
                        window.showDirectory(index);
                        running = false;
                    }
                }
            }
        }
    }

    ListModel {
        id: treeModel
        ListElement {
            name: "Inbox"
        }
        ListElement {
            name: "Outbox"
        }
    }
}
