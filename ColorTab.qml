import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Item {

    id: root
    width: 580
    height: 400
    SystemPalette { id: palette }
    clip: true

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

            Label{
                text: "The color is used to distinguish between the different types of shots present in the video."
            }

           // Item { Layout.preferredHeight: 5 } // padding

            CheckBox{
                text: "Use color?"
                id: useColor
                objectName: "useColor"
                checked: false

                onCheckedChanged:{
                    if(useColor.checked){
                        subImagesCb.enabled = true
                        shotCheckboxes.enabled = true
                        processLabel.enabled = true
                        shotLabel.enabled = true
                    }
                    else{
                        subImagesCb.enabled = false
                        shotCheckboxes.enabled = false
                        processLabel.enabled = false
                        shotLabel.enabled = false
                    }

                }
            }

            Label{
                id: processLabel
                enabled: false
                font.bold: true
                text: "Process accuracy:"
            }

            ComboBox{
                id: subImagesCb
                enabled: false
                objectName: "subimmageCB"
                // model: [ "1 (Fast)", "2", "3", "4", "5 (Slow)" ]
                //model: ["5 (Slow)", "4", "3", "2", "1 (Fast)"]
                //corresponde a 5, 3, 1
                model: ["Best", "Better", "Good"]

            }

            Item { Layout.preferredHeight: 5 } //extra spacing

            Label{
                id: shotLabel
                enabled: false
                text: "Type of shots to use:"
                font.bold: true
            }
            RowLayout{
                id: shotCheckboxes
                enabled: false
                objectName: "shotCheckboxes"
                spacing: 25

                ColumnLayout{
                    CheckBox{
                        text: "Long Shot"
                        objectName: "LONG_SHOT"
                        checked: true
                    }
                    Label{
                        text: " E.g. shots of the field."
                    }
                }

                ColumnLayout{
                    CheckBox{
                        text: "Closeup Shot"
                        objectName: "CLOSEUP_SHOT"
                        checked: true
                    }
                    Label{
                        text: "E.g. shots of individual players."
                    }
                }

                ColumnLayout{
                    CheckBox{
                        text: "Out of Field Shot"
                        objectName: "OUT_OF_FIELD"
                        checked: true
                    }
                    Label{
                        text: "E.g. shots of the audience."
                    }
                }

            }

        }
    }

}
