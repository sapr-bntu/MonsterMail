import QtQuick 1.1

Rectangle {
    id: form
    width: 800
    height: 400

    VisualItemModel {
        id: itemmodel

        Settings {
        }

        MainWindow {
            Component.onCompleted: {
            }
        }

        Rectangle {
            FormNewMessage {
                width: form.width
                height: form.height
            }
        }
    }

    ListView {
        id: screens
        highlightResizeSpeed: 1000
        highlightMoveSpeed: 1000
        flickDeceleration: 1000
        cacheBuffer: 3
        flickableDirection: Flickable.AutoFlickDirection
        maximumFlickVelocity: 8000
        boundsBehavior: Flickable.StopAtBounds
        model: itemmodel
    }
    Component.onCompleted: {
        screens.currentIndex = 1
    }
}
