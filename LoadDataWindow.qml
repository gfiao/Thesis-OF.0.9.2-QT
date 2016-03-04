import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Window {
    id: qmlWindow
    title: "Emotion Data Parameters"
    width: 400; height: 350

    TextField {
        id: textField1
        x: 197
        y: 52
        inputMask: qsTr("")
        placeholderText: qsTr("Value")
        //inputMethodHints: Qt.ImhDigitsOnly
        validator: IntValidator{bottom: 0; top: 100}
    }

    Text {
        id: text1
        x: 104
        y: 55
        text: qsTr("Interval:")
        font.pixelSize: 13
    }

    Button {
        id: button1
        x: 163
        y: 260
        text: qsTr("Load Data")
    }

    //Other properties
}
