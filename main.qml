import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5
import QtQuick.Extras 1.4

ApplicationWindow {
    id: qmlWindow
    minimumWidth: 400
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

            signal mouseAreaSignal(var signal)
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

            signal mouseAreaSignal(var signal)
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

            signal mouseAreaSignal(var signal)
        }
    }


    Image {
        id: volumeImage
        x: 296
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
        x: 329
        y: 12
        width: 148
        height: 20
        value: 0.0

        signal sliderSignal(var msg)
        onValueChanged: slider.sliderSignal(value)
    }



    function myQmlFunction(msg) {
        console.log("Got message:", msg)
        return "some return value"
    }



    //=================================================
    //LOAD DATA WINDOW
    //=================================================
    Window {
        visible: false
        objectName: "loadDataWindow"
        id: qmlWindow2
        title: "Emotion Data Parameters"
        //width: child.width; height: child.height

        Item {
            id: item
            width: 580
            height: 400
            SystemPalette { id: palette }
            clip: true


            ScrollView {
                width: parent.width
                height: parent.height
                anchors.rightMargin: 20
                anchors.topMargin: 0
                id: scrollView
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    //bottom: bottomBar.top
                    leftMargin: -8
                }
                ColumnLayout {
                    spacing: 8
                    Item { Layout.preferredHeight: 4 } // padding

                    Button {
                        objectName: "loadDataFile"
                        id: loadDataFile
                        x: 163
                        y: 35
                        text: qsTr("Load File")
                    }

                    Label {
                        id: interval_label
                        x: 56
                        y: 83
                        text: qsTr("Interval:")
                        font.bold: true
                    }

                    TextField {
                        objectName: "interval_textfield"
                        id: interval_textfield
                        x: 56
                        y: 109
                        inputMask: qsTr("")
                        placeholderText: qsTr("Value")
                        validator: IntValidator{bottom: 0; top: 100}
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

                    Label {
                        visible: false
                        id: dynInter_label
                        x: 56
                        y: 208
                        text: qsTr("Dynamic Interval Value:")
                        font.bold: true
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

                    Button {
                        objectName: "loadDataParameters"
                        id: loadDataParameters
                        x: 163
                        y: 286
                        text: qsTr("Load Data")
                    }

                }
            }

        }
    }
    //==============================
    // END OF LOAD DATA WINDOW
    //===============================



}
