import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: qmlWindow
    width: 600; height: 400
    visible: true
    title: "QML Window"


    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt Quick Controls Gallery"
        informativeText: "This example demonstrates most of the available Qt Quick Controls."
    }

    menuBar:  MenuBar {
        id: menu

        Menu {
            title: "File"

            MenuItem {

                objectName: "loadData"
                text: "Load Data"
                onTriggered: {
                    var component = Qt.createComponent("LoadDataWindow.qml")
                    var window    = component.createObject(qmlWindow)
                    window.show()
                }

            }

            MenuItem {
                objectName: "loadVideo"
                text: "Load Video"
            }
        }

        Menu {
            title: "Help"
            MenuItem {
                text: "About..."
                onTriggered: aboutDialog.open()
            }
        }
    }

    Text {
        x: 75; y: 100
        height: 25; width: 150
        text: "Video Volume"
    }

    Slider {
        id: slider;
        objectName: "videoVolume";
        x: 75; y: 125
        height: 25; width: 150
        value: 0.0
        signal sliderSignal(var msg)
        onValueChanged: slider.sliderSignal(value)
    }

    function myQmlFunction(msg) {
        console.log("Got message:", msg)
        return "some return value"
    }
}
