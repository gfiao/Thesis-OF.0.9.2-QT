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


            RowLayout{
                Label{
                    text: "Create a new file?:"
                    font.bold: true
                }
            }
            RowLayout{
                id: newFileLayout

                TextField{
                    objectName: "cutThreshold"
                    placeholderText: qsTr("Choose the threshold")
                    validator: DoubleValidator{locale: Qt.UTC;bottom: 0; top: 1; decimals: 4}

                    onAccepted: newCutButton.enabled = true
                }
                Button{
                    id: newCutButton
                    text: "Create new file"
                    objectName: "newCutButton"
                    enabled: false

                    onClicked: {
                        if (existingButtonLayout.visible)
                            existingButtonLayout.visible = false
                    }

                }
            }

            Item { Layout.preferredHeight: 4 } // padding
            RowLayout{
                id: existingButtonLayout
                spacing: 15

                Button{
                    text: "Load existing file"
                    objectName: "existingCutButton"

                    onClicked: {
                        if (cutsList.visible)
                            cutsList.visible = false
                        else cutsList.visible = true
                    }
                }

                Label{
                    objectName: "loadedCutFile"
                }
            }

            TableView {
                id: cutsList
                objectName: "cutsList"
                visible: false

                signal currentRow(var row)

                TableViewColumn {
                    role: "timestamp"
                    title: "Timestamp"
                }

                onActivated: cutsList.currentRow(row)
            }
        }
    }

}

