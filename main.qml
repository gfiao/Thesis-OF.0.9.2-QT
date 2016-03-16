import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Extras 1.4

ApplicationWindow {
    id: qmlWindow
    minimumWidth: 500
    minimumHeight: 500

    width: 500
    height: 500

    visible: true
    title: "QML Window"

    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt Quick Controls Gallery"
        informativeText: "This example demonstrates most of the available Qt Quick Controls."
    }

    LoadDataWindow{
        id: loadDataWindow
    }

    menuBar:  MenuBar {
        id: menu

        Menu {
            title: "File"

            MenuItem {

                objectName: "loadData"
                text: "Load Data"
                onTriggered: {
                    loadDataWindow.visible = true
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


    Item{
        id: mediaPlayerButtons
        width: 500
        height: 51

        Image {
            id: playImage
            x: 10
            y: 12
            objectName: "playImage"
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: "qrc:/glyphicons_free/glyphicons/png/glyphicons-174-play.png"

            MouseArea{
                objectName: "playMouseArea"
                width: parent.width
                height: parent.height
            }
        }

        Image{
            id: pauseImage
            x: 53
            y: 12
            objectName: "pauseImage"
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: "qrc:/glyphicons_free/glyphicons/png/glyphicons-175-pause.png"

            MouseArea{
                objectName: "pauseMouseArea"
                width: parent.width
                height: parent.height
            }
        }

        Image {
            id: stopImage
            x: 98
            y: 12
            objectName: "stopImage"
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: "qrc:/glyphicons_free/glyphicons/png/glyphicons-176-stop.png"

            MouseArea{
                objectName: "stopMouseArea"
                width: parent.width
                height: parent.height
            }
        }


        Image {
            id: volumeImage
            x: 304
            y: 12
            objectName: "volumeImage"
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: "qrc:/glyphicons_free/glyphicons/png/glyphicons-185-volume-up.png"
        }

        Slider {
            id: slider;
            objectName: "videoVolume";
            x: 342
            y: 12
            width: 148
            height: 20
            value: 0.0

            signal sliderSignal(var msg)
            onValueChanged: slider.sliderSignal(value)
        }
    }

    TabView{
        objectName: "tabView"
       // enabled: false
        x: 10
        anchors.top: mediaPlayerButtons.bottom
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.bottom: bottomBar.top
        anchors.left: parent.left

        Tab{
            title: "Emotions"
            EmotionsTab{}
        }

        Tab{
            title: "Color"
            ColorTab{}
        }

        Tab{
            title: "Movement"
            MovementTab{}
        }

        Tab{
            title: "Cut Detection"
            CutDetectionTab{}
        }
    }

    Rectangle{ //to house the run algorithm button and other stuff
        id: bottomBar
        y: 452
        height: 38
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

    }


    function myQmlFunction(msg) {
        console.log("Got message:", msg)
        return "some return value"
    }



}
