import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Window {
    id: qmlWindow
    width: 600; height: 400

    Text{
        text: "TOP KEK. TOP. KEK."
    }

    Button {
        id: button1
        x: 58
        y: 59
        text: qsTr("Button")
    }

    Button {
        id: button2
        x: 411
        y: 270
        text: qsTr("Button")
    }

    Button {
        id: button3
        x: 71
        y: 389
        text: qsTr("Button")
    }

    Button {
        id: button4
        x: 455
        y: 52
        text: qsTr("Button")
    }

    //Other properties
}
