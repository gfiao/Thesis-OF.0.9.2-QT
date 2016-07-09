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

            CheckBox{
                id: useEmotions
                objectName: "useEmotions"
                text: "Use emotions"
                checked: true

                onCheckedChanged: {
                    if(!useEmotions.checked){
                        checkboxRow.enabled = false
                        minNrEmotionsRow.enabled = false
                        emotionsLabel.enabled = false
                    }
                    else{
                        checkboxRow.enabled = true
                        minNrEmotionsRow.enabled = true
                        emotionsLabel.enabled = true
                    }
                }
            }

            Label {
                id: emotionsLabel
                font.bold: true
                text: "Emotions to be used:"
            }

            RowLayout{
                id: checkboxRow
                objectName: "checkboxRow"
                spacing: 15

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

            /* RowLayout{
                id: minNrEmotionsRow
                Label{
                    text: "Minimum number of emotions:"
                    font.bold: true
                }
                TextField{
                    objectName: "minNumberOfEmotions"
                    placeholderText: "Minimum number of emotions"
                    validator: IntValidator{bottom: 0; top: 1000}
                }
            }*/

            ColumnLayout{
                spacing: 10
                id: intervalRow
                Label{
                    text: "Clustering interval:"
                    font.bold: true
                }
                TextField{
                    id: emotionInterval
                    objectName: "emotionInterval"
                    placeholderText: "Default is 5"
                    validator: IntValidator{bottom: 1; top: 100}
                }
               /* Label{
                    text: {
                        if(emotionInterval.text != "")
                            "Interval is set at " + emotionInterval.text + " seconds"
                        else
                            "Interval is set at 5 seconds"
                    }
                }*/
            }
            ChartWindow{
                id: chartWindow
                objectName: "chartWindow"
            }

            Button{
                text: "See Emotions Chart Over Time"
                objectName: "showChart"
                id: showChart

                onClicked: {
                    if(chartWindow.visible)
                        chartWindow.visible = false;
                    else
                        chartWindow.visible = true
                }
            }
        }
    }
}
