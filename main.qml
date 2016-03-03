import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Window {
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

    MenuBar {
        id: menu

        Menu {
            title: "File"

            MenuItem {
                text: "Load Data"
            }

            MenuItem {
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

    Button {
        objectName: "changeColorButton";
        x: 75; y: 40
        height: 25; width: 150
        text: "Load Video"
        z: 0
        rotation: 0
        transformOrigin: Item.Center
    }

    Text {
        x: 75; y: 100
        height: 25; width: 150
        text: "Video Volume"
    }

    Slider {
        id: slider;
        objectName: "changePositionSlider";
        x: 75; y: 125
        height: 25; width: 150
        value: 0.0
        signal sliderSignal(var msg)
        onValueChanged: slider.sliderSignal(value)
    }

    Button {
        x: 257
        y: 40
        width: 150
        height: 25
        text: "Load Data"
        z: 0
        objectName: "changeColorButton"
        transformOrigin: Item.Center
        rotation: 0
    }

    function myQmlFunction(msg) {
        console.log("Got message:", msg)
        return "some return value"
    }

}
