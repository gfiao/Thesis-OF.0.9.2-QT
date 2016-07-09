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
                text: "Max length of the highlight video:"
                font.bold: true
            }
            TextField{
                objectName: "summaryDuration"
                placeholderText: qsTr("Minutes (default is 3m)")
            }

            Label{
                text: "Max length of each clip:"
                font.bold: true
            }
            TextField{
                objectName: "clipDuration"
                placeholderText: qsTr("Seconds (default is 20s)")
                validator: IntValidator{bottom: 0; top: 45}
            }

            CheckBox{
                objectName: "soundCheckbox"
                text: "Use sound"
                checked: true
            }
            Label{
                text: "This feature might be useful to extract clips that have high frequency values."
            }

            CheckBox{
                id: useCuts
                objectName: "useCuts"
                text: "Use cuts"
            }
            Label{
                text: "This feature might be useful to extract clips that focus on the sports event’s action."
            }

            CheckBox{
                objectName: "fadeInOut"
                text: "Fade between clips"
                checked: false
            }

        }
    }


}
