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


           /* ComboBox{
                objectName: "comboBox"
                enabled: false
                width: 200
            }*/

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


            /* Label {
                font.bold: true
                text: "Message dialog properties:"
            }
            CheckBox {
                id: messageDialogModal
                text: "Modal"
                checked: true
                Binding on checked { value: messageDialog.modality != Qt.NonModal }
            }
            RowLayout {
                CheckBox {
                    id: customizeTitle
                    text: "Window Title"
                    Layout.alignment: Qt.AlignBaseline
                    checked: true
                }
                TextField {
                    id: windowTitleField
                    Layout.alignment: Qt.AlignBaseline
                    Layout.fillWidth: true
                    text: "Alert"
                }
            }
            Label { text: "Icon:" }
            Flow {
                spacing: 8
                Layout.fillWidth: true
                property bool updating: false
                function updateIcon(icon, checked) {
                    if (updating) return
                    updating = true
                    messageDialog.icon = (checked ? icon : StandardIcon.NoIcon)
                    for (var i = 0; i < children.length; ++i)
                        if (children[i].icon !== icon)
                            children[i].checked = false
                    updating = false
                }

                CheckBox {
                    id: iconInformation
                    text: "Information"
                    property int icon: StandardIcon.Information
                    onCheckedChanged: parent.updateIcon(icon, checked)
                }

                CheckBox {
                    id: iconWarning
                    text: "Warning"
                    checked: true
                    property int icon: StandardIcon.Warning
                    onCheckedChanged: parent.updateIcon(icon, checked)
                    Component.onCompleted: parent.updateIcon(icon, true)
                }

                CheckBox {
                    id: iconCritical
                    text: "Critical"
                    property int icon: StandardIcon.Critical
                    onCheckedChanged: parent.updateIcon(icon, checked)
                }

                CheckBox {
                    id: iconQuestion
                    text: "Question"
                    property int icon: StandardIcon.Question
                    onCheckedChanged: parent.updateIcon(icon, checked)
                }
            }

            RowLayout {
                CheckBox {
                    id: customizeText
                    text: "Primary Text"
                    Layout.alignment: Qt.AlignBaseline
                    checked: true
                }
                TextField {
                    id: textField
                    Layout.alignment: Qt.AlignBaseline
                    Layout.fillWidth: true
                    text: "Attention Please"
                }
            }
            RowLayout {
                CheckBox {
                    id: customizeInformativeText
                    text: "Informative Text"
                    Layout.alignment: Qt.AlignBaseline
                    checked: true
                }
                TextField {
                    id: informativeTextField
                    Layout.alignment: Qt.AlignBaseline
                    Layout.fillWidth: true
                    text: "Be alert!"
                }
            }
            Label { text: "Buttons:" }
            Flow {
                spacing: 8
                Layout.fillWidth: true
                Layout.preferredWidth: root.width - 30
                property bool updating: false
                function updateButtons(button, checked) {
                    if (updating) return
                    updating = true
                    var buttons = 0
                    for (var i = 0; i < children.length; ++i)
                        if (children[i].checked)
                            buttons |= children[i].button
                    if (!buttons)
                        buttons = StandardButton.Ok
                    messageDialog.standardButtons = buttons
                    updating = false
                }

                CheckBox {
                    text: "Help"
                    property int button: StandardButton.Help
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Abort"
                    property int button: StandardButton.Abort
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Close"
                    property int button: StandardButton.Close
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Cancel"
                    property int button: StandardButton.Cancel
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "NoToAll"
                    property int button: StandardButton.NoToAll
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "No"
                    property int button: StandardButton.No
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "YesToAll"
                    property int button: StandardButton.YesToAll
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Yes"
                    property int button: StandardButton.Yes
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Ignore"
                    property int button: StandardButton.Ignore
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "Retry"
                    property int button: StandardButton.Retry
                    onCheckedChanged: parent.updateButtons(button, checked)
                }

                CheckBox {
                    text: "OK"
                    checked: true
                    property int button: StandardButton.Ok
                    onCheckedChanged: parent.updateButtons(button, checked)
                }
            }
            RowLayout {
                CheckBox {
                    id: customizeDetailedText
                    text: "Detailed Text"
                    Layout.alignment: Qt.AlignBaseline
                    checked: true
                }
                TextField {
                    id: detailedTextField
                    Layout.alignment: Qt.AlignBaseline
                    Layout.fillWidth: true
                    text: "The world needs more lerts."
                }
            }
            CheckBox {
                id: messageDialogVisible
                text: "Visible"
                Binding on checked { value: messageDialog.visible }
            }
            Label {
                id: lastChosen
            }
        }
    }*/

        }
    }
}
