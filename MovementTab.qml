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
            spacing: 8
            Item { Layout.preferredHeight: 4 } // padding


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

                Text {
                    text: qsTr(" to ")
                }

                TextField {
                    placeholderText: qsTr("End Timestamp")
                    validator: IntValidator{bottom: 0; top: 10000}
                }
            }
        }
    }


}
