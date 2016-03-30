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

            Label {
                font.bold: true
                text: "What emotions will be used?:"
            }

            RowLayout{
                id: checkboxRow
                objectName: "checkboxRow"

                CheckBox{
                    text: "Anger"
                    checked: true
                }
                CheckBox{
                    text: "Connectedness"
                    checked: true
                }
                CheckBox{
                    text: "Elation"
                    checked: true
                }
                CheckBox{
                    text: "Surprise"
                    checked: true
                }
                CheckBox{
                    text: "Unhappiness"
                    checked: true
                }
                CheckBox{
                    text: "Worry"
                    checked: true
                }
            }

            RowLayout{
                Label{
                    text: "Mininum number of emotions:"
                    font.bold: true
                }
                TextField{
                    objectName: "minNumberOfEmotions"

                    validator: IntValidator{bottom: 0; top: 1000}
                }
            }
        }
    }
}
