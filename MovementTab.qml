import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Item {
    width: 580
    height: 400
    SystemPalette { id: palette }
    clip: true

    ScrollView {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            leftMargin: 12
        }
        ColumnLayout {
            spacing: 10
            Item { Layout.preferredHeight: 4 } // padding




            Label{
                text: "First half:"
                font.bold: true
            }
            RowLayout{
                id: firstDirectionRow
                objectName: "firstDirectionRow"

                CheckBox{
                    text: "Left"
                    checked: true
                }
                CheckBox{
                    text: "Right"
                    checked: true
                }
            }

            Label{
                text: "Timeframe:"
                font.bold: true
            }
            RowLayout{
                id: timeframeRow
                objectName: "timeframeRow"

                //more validation will be done on the C++ side
                TextField {
                    placeholderText: qsTr("Start Timestamp")
                    validator: IntValidator{bottom: 0; top: 10000}
                }
            }

            Label{
                text: "Second half:"
                font.bold: true
            }
            RowLayout{
                id: secondDirectionRow
                objectName: "secondDirectionRow"

                CheckBox{
                    text: "Left"
                    checked: true
                }
                CheckBox{
                    text: "Right"
                    checked: true
                }
            }
        }
    }


}
