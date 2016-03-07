import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Window {
    objectName: "loadDataWindow"
    id: qmlWindow
    title: "Emotion Data Parameters"
    width: 400; height: 350

    TextField {
        id: interval_textfield
        x: 56
        y: 109
        inputMask: qsTr("")
        placeholderText: qsTr("Value")
        validator: IntValidator{bottom: 0; top: 100}
    }

    Button {
        objectName: "loadDataParameters"
        id: loadDataParameters
        x: 163
        y: 286
        text: qsTr("Load Data")
    }

    Button {
        objectName: "loadDataFile"
        id: loadDataFile
        x: 163
        y: 35
        text: qsTr("Load File")
    }

    RadioButton {
        id: dynInter_radio
        x: 56
        y: 167
        text: qsTr("Dynamic Interval")
        onClicked: {
            if(dynInter_textfield.visible == false){
                dynInter_textfield.visible = true
                dynInter_label.visible = true
            }
            else{
                dynInter_textfield.visible = false
                dynInter_label.visible = false
            }

        }
    }

    TextField {
        visible: false
        id: dynInter_textfield
        x: 56
        y: 239
        placeholderText: qsTr("Value")
        validator: IntValidator{bottom: 0; top: 100}
    }

    Label {
        id: interval_label
        x: 56
        y: 83
        text: qsTr("Interval")
    }

    Label {
        visible: false
        id: dynInter_label
        x: 56
        y: 208
        text: qsTr("Dynamic Interval Value:")
    }

}
