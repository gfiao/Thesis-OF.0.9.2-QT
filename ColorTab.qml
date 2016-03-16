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
            }

            Label{
                font.bold: true
                text: "How many subimages will be processed?:"
            }

            ComboBox{
                objectName: "subimmageCB"
                model: [ "None", "2", "4", "6", "9" ]

            }

        }
    }

}
