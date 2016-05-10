import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window{
    visible: false
    objectName: "setScoresWindow"
    id: setScoresWindow
    width: 300
    height: 300
    title: "Set Scores"

    minimumWidth: 300
    minimumHeight: 300
    maximumWidth: 300
    maximumHeight: 300

    Label{
        id: emotionLabel
        x: 116
        y: 32
        text: "Emotions - 0.6"
    }
    Slider{
        objectName: "emotionSlider"
        id: emotionSlider
        value: 0.6
        stepSize: 0.01
        x: 51
        y: 68
        onValueChanged:{
            audioSlider.value = 1 - emotionSlider.value
            emotionLabel.text = "Emotions - " + emotionSlider.value
        }
    }

    Label{
        id: audioLabel
        x: 124
        y: 128
        text: "Audio - 0.4"
    }
    Slider{
        objectName: "audioSlider"
        id: audioSlider
        value: 0.4
        stepSize: 0.01
        x: 50
        y: 166
        onValueChanged:{
            emotionSlider.value = 1 - audioSlider.value
            audioLabel.text = "Audio - " + audioSlider.value
        }
    }

    Button{
        x: 113
        y: 225
        text: "Ok"

        onClicked: setScoresWindow.close()
    }

}
