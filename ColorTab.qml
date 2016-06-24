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

            /* CheckBox{
                id: timeframeCheckbox
                objectName: "timeframeCheckbox"
                text: "Specify a timeframe?"
            }

            Label {
                id: timeframeLabel
                font.bold: true
                text: "Choose the time frame:"
                visible: {
                    if (timeframeCheckbox.checked)
                        true
                    else false
                }
            }

            RowLayout{
                id: timeframeRow
                objectName: "timeframeRow"

                //more validation will be done on the C++ side
                TextField {
                    placeholderText: qsTr("Start Timestamp")
                    validator: IntValidator{bottom: 0; top: 10000}
                }

                Text {
                    text: qsTr(" to ")
                }

                TextField {
                    placeholderText: qsTr("End Timestamp")
                    validator: IntValidator{bottom: 0; top: 10000}
                }

                visible: {
                    if (timeframeCheckbox.checked)
                        true
                    else false
                }
            }*/

            Label{
                font.bold: true
                text: "How precise do you want the color processing to be?:"
            }

            ComboBox{
                objectName: "subimmageCB"
                // model: [ "1 (Fast)", "2", "3", "4", "5 (Slow)" ]
                model: ["5 (Slow)", "4", "3", "2", "1 (Fast)"]

            }

            Item { Layout.preferredHeight: 5 } //extra spacing

            Label{
                text: "What type of shots are you looking for?"
                font.bold: true
            }
            RowLayout{
                objectName: "shotCheckboxes"
                spacing: 25

                CheckBox{
                    text: "Long Shot"
                    checked: true
                }
                CheckBox{
                    text: "Closeup Shot"
                    checked: true
                }
                CheckBox{
                    text: "Out of Field Shot"
                    checked: true
                }
            }

        }
    }

}
