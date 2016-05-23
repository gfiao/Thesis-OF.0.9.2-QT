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

            CheckBox{
                id: useMov
                objectName: "useMov"
                checked: false
                text: "Use movement in the algorithm?"

                onCheckedChanged: {
                    if(useMov.checked == false){
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
                id: timeframe
                text: "Timeframe:"
                font.bold: true
            }
            RowLayout{
                id: timeframeRow
                objectName: "timeframeRow"

                TextField {
                    objectName: "halfTime"
                    placeholderText: qsTr("Start Timestamp")
                    validator: IntValidator{bottom: 0; top: 10000}
                }
            }

            Label{
                id: secondHalf
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
