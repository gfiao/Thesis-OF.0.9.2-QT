import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    visible: false
    objectName: "loadDataWindow"
    id: loadDataWindow
    title: "Emotion Data Parameters"

    minimumWidth: 335
    minimumHeight: 250

    Item {
        id: item
        width: parent.width
        height: parent.height

        ScrollView {
            id: scrollView
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                leftMargin: 12
            }

            ColumnLayout {
                spacing: 8
                Item { Layout.preferredHeight: 4 } // padding

                RowLayout{
                    Button {
                        objectName: "loadDataFile"
                        id: loadDataFile
                        text: qsTr("Load CSV File")
                    }

                    Label{
                        objectName: "loadFileLabel"
                        visible: false
                        text: ""
                    }
                }
                Item { Layout.preferredHeight: 5 } // padding

                RowLayout{
                    Label {
                        id: interval_label
                        text: qsTr("Interval:")
                        font.bold: true
                    }

                    TextField {
                        objectName: "interval_textfield"
                        id: interval_textfield
                        inputMask: qsTr("")
                        placeholderText: qsTr("Value")
                        validator: IntValidator{bottom: 0; top: 100}
                    }
                }

                Item { Layout.preferredHeight: 5 } // padding
                RadioButton {
                    objectName: "dynInter_radio"
                    id: dynInter_radio
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

                RowLayout{
                    Label {
                        visible: false
                        id: dynInter_label
                        text: qsTr("Dynamic Interval Value:")
                        font.bold: true
                    }

                    TextField {
                        visible: false
                        objectName: "dynInter_textfield"
                        id: dynInter_textfield
                        placeholderText: qsTr("Value")
                        validator: IntValidator{bottom: 0; top: 100}
                    }
                }

                Item { Layout.preferredHeight: 5 } // padding
                Button {
                    objectName: "loadDataParameters"
                    id: loadDataParameters
                    text: qsTr("Load Data")
                }
            }
        }

    }
}
