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
                text: "How precise do you want the color processing to be?:"
            }

            ComboBox{
                id: subImagesCb
                enabled: false
                objectName: "subimmageCB"
                // model: [ "1 (Fast)", "2", "3", "4", "5 (Slow)" ]
                model: ["5 (Slow)", "4", "3", "2", "1 (Fast)"]

            }

            Item { Layout.preferredHeight: 5 } //extra spacing

            Label{
                id: shotLabel
                enabled: false
                text: "What type of shots are you looking for?"
                font.bold: true
            }
            RowLayout{
                id: shotCheckboxes
                enabled: false
                objectName: "shotCheckboxes"
                spacing: 25

                CheckBox{
                    text: "Long Shot"
                    objectName: "LONG_SHOT"
                    checked: true
                }
                CheckBox{
                    text: "Closeup Shot"
                    objectName: "CLOSEUP_SHOT"
                    checked: true
                }
                CheckBox{
                    text: "Out of Field Shot"
                    objectName: "OUT_OF_FIELD"
                    checked: true
                }
            }

        }
    }

}
