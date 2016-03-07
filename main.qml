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
                   /* var component = Qt.createComponent("LoadDataWindow.qml")
                    var window    = component.createObject(qmlWindow)
                    window.show()*/
                    qmlWindow2.visible = true;
                }

            }

            MenuItem {
                objectName: "loadVideo"
                text: "Load Video"
            }

            MenuSeparator{}

            MenuItem{
                objectName: "clearSelection"
                text: "Clear Selection"
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



    Window {
        visible: false
        objectName: "loadDataWindow"
        id: qmlWindow2
        title: "Emotion Data Parameters"
        width: 400; height: 350

        TextField {
            objectName: "interval_textfield"
            id: interval_textfield
            x: 56
            y: 109
            inputMask: qsTr("")
            placeholderText: qsTr("Value")
            validator: IntValidator{bottom: 0; top: 100}
        }

        Button {
            objectName: "loadDataParameters"
            id: loadDataParameters
            x: 163
            y: 286
            text: qsTr("Load Data")
        }

        Button {
            objectName: "loadDataFile"
            id: loadDataFile
            x: 163
            y: 35
            text: qsTr("Load File")
        }

        RadioButton {
            objectName: "dynInter_radio"
            id: dynInter_radio
            x: 56
            y: 167
            text: qsTr("Dynamic Interval")
            onClicked: {
                if(dynInter_textfield.visible == false){
                    dynInter_textfield.visible = true
                    dynInter_label.visible = true
                }
                else{
                    dynInter_textfield.visible = false
                    dynInter_label.visible = false
                }

            }
        }

        TextField {
            visible: false
            objectName: "dynInter_textfield"
            id: dynInter_textfield
            x: 56
            y: 239
            placeholderText: qsTr("Value")
            validator: IntValidator{bottom: 0; top: 100}
        }

        Label {
            id: interval_label
            x: 56
            y: 83
            text: qsTr("Interval")
        }

        Label {
            visible: false
            id: dynInter_label
            x: 56
            y: 208
            text: qsTr("Dynamic Interval Value:")
        }

    }

}
