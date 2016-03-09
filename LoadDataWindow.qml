import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Window {
    objectName: "loadDataWindow"
    id: qmlWindow2
    title: "Emotion Data Parameters"
    width: child.width; height: child.height

    Item {
        id: item
        width: 580
        height: 400
        visible: false
        SystemPalette { id: palette }
        clip: true


        ScrollView {
            id: scrollView
            height: 382
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottom: bottomBar.top
                leftMargin: 12
            }
            ColumnLayout {
                width: 440
                height: 327
                spacing: 8
                Item { Layout.preferredHeight: 4 } // padding
                Label {
                    font.bold: true
                    text: "File dialog properties:"
                }
                CheckBox {
                    id: fileDialogModal
                    text: "Modal"
                    checked: true
                    Binding on checked { value: fileDialog.modality != Qt.NonModal }
                }
                CheckBox {
                    id: fileDialogSelectFolder
                    text: "Select Folder"
                    Binding on checked { value: fileDialog.selectFolder }
                }
                CheckBox {
                    id: fileDialogSelectExisting
                    text: "Select Existing Files"
                    checked: true
                    Binding on checked { value: fileDialog.selectExisting }
                }
                CheckBox {
                    id: fileDialogSelectMultiple
                    text: "Select Multiple Files"
                    Binding on checked { value: fileDialog.selectMultiple }
                }
                CheckBox {
                    id: fileDialogOpenFiles
                    text: "Open Files After Accepting"
                }
                CheckBox {
                    id: fileDialogSidebarVisible
                    text: "Show Sidebar"
                    checked: fileDialog.sidebarVisible
                    Binding on checked { value: fileDialog.sidebarVisible }
                }
                CheckBox {
                    id: fileDialogVisible
                    text: "Visible"
                    Binding on checked { value: fileDialog.visible }
                }
            }
        }

    }

  /*  ScrollView{
        implicitWidth: parent.width
        implicitHeight: parent.height

        ColumnLayout {
            width: parent.width
            height: parent.height
            spacing: 12

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
                text: qsTr("Interval")
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
    }*/
}
