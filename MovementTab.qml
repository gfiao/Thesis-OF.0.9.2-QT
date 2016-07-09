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
                text: "The movement is used to distinguish between which direction the play is going."
            }

            //Item { Layout.preferredHeight: 5 } // padding


            CheckBox{
                id: useMov
                objectName: "useMov"
                checked: false
                text: "Use movement"

                onCheckedChanged: {
                    if(!useMov.checked){
                        firstDirectionRow.enabled = false
                        timeframeRow.enabled = false
                        secondDirectionRow.enabled = false
                        firstHalf.enabled = false
                        timeframe.enabled = false
                        secondHalf.enabled = false
                    }
                    else{
                        firstDirectionRow.enabled = true
                        timeframeRow.enabled = true
                        secondDirectionRow.enabled = true
                        firstHalf.enabled = true
                        timeframe.enabled = true
                        secondHalf.enabled = true
                    }
                }
            }


            Label{
                id: firstHalf
                text: "Extract clips from the first half:"
                font.bold: true
                enabled: false
            }
            ColumnLayout{
                spacing: 8
                id: firstDirectionRow
                objectName: "firstDirectionRow"
                enabled: false

                CheckBox{
                    text: "Team attacking on the left"
                    checked: true
                }
                CheckBox{
                    text: "Team attacking on the right"
                    checked: true
                }
            }

            /*Label{
                id: timeframe
                text: "Half-time:"
                font.bold: true
                enabled: false
            }
            RowLayout{
                id: timeframeRow
                objectName: "timeframeRow"
                enabled: false

                TextField {
                    objectName: "halfTime"
                    placeholderText: qsTr("When is half-time?(minutes)")
                    validator: IntValidator{bottom: 0; top: 10000}
                }
            }*/

            Label{
                id: secondHalf
                text: "Extract clips from the second half:"
                font.bold: true
                enabled: false
            }
            ColumnLayout{
                spacing: 8
                id: secondDirectionRow
                objectName: "secondDirectionRow"
                enabled: false

                CheckBox{
                    text: "Team attacking on the left"
                    checked: true
                }
                CheckBox{
                    text: "Team attacking on the right"
                    checked: true
                }
            }
        }
    }


}
