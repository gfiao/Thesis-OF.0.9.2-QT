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
        // RowLayout{
        //  spacing: 20
        ColumnLayout {
            spacing: 8
            Item { Layout.preferredHeight: 4 } // padding

            RowLayout{
                spacing: 15
                //===============
                Button{
                    text: "Create new file"
                    objectName: "newCutButton"

                    onClicked: {
                        if (newFileLayout.visible)
                            newFileLayout.visible = false
                        else newFileLayout.visible = true
                    }
                }

                Button{
                    text: "Load existing file"
                    objectName: "existingCutButton"

                    onClicked: {
                        if (cutsList.visible)
                            cutsList.visible = false
                        else cutsList.visible = true
                    }
                }
            }
            RowLayout{
                id: newFileLayout
                visible: false
                Label{
                    text: "Choose the threshold:"
                }
                TextField{
                    objectName: "cutThreshold"
                    placeholderText: qsTr("Threshold")
                    validator: DoubleValidator{bottom: 0; top: 1; decimals: 4}
                }
                Button{
                    text: "Do it!"
                }
            }

            TableView {
                //width: 180; height: 200
                id: cutsList
                objectName: "cutsList"
                visible: false

                TableViewColumn {
                    role: "name"
                    title: "Name"
                    width: 100
                }
                TableViewColumn {
                    role: "number"
                    title: "Number"
                    width: 200
                }

                model: ListModel {
                    ListElement {
                        name: "Bill Smith"
                        number: "555 3264"
                    }
                    ListElement {
                        name: "John Brown"
                        number: "555 8426"
                    }
                    ListElement {
                        name: "Sam Wise"
                        number: "555 0473"
                    }
                    ListElement {
                        name: "Bill Smith"
                        number: "555 3264"
                    }
                    ListElement {
                        name: "John Brown"
                        number: "555 8426"
                    }
                    ListElement {
                        name: "Sam Wise"
                        number: "555 0473"
                    }
                    ListElement {
                        name: "Bill Smith"
                        number: "555 3264"
                    }
                    ListElement {
                        name: "John Brown"
                        number: "555 8426"
                    }
                    ListElement {
                        name: "Sam Wise"
                        number: "555 0473"
                    }
                    ListElement {
                        name: "Bill Smith"
                        number: "555 3264"
                    }
                    ListElement {
                        name: "John Brown"
                        number: "555 8426"
                    }
                    ListElement {
                        name: "Sam Wise"
                        number: "555 0473"
                    }
                    ListElement {
                        name: "Bill Smith"
                        number: "555 3264"
                    }
                    ListElement {
                        name: "John Brown"
                        number: "555 8426"
                    }
                    ListElement {
                        name: "Sam Wise"
                        number: "555 0473"
                    }
                }
            }
        }

    }
}
