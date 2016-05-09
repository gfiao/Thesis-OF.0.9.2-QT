import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window{
    visible: false
    objectName: "setScoresWindow"
    id: setScoresWindow
    title: "Set Scores"

    minimumWidth: 300
    minimumHeight: 300
    maximumWidth: 300
    maximumHeight: 300

    Label{
        x: 124
        y: 30
        text: "Emotions"
    }
    Slider{
        objectName: "emotionSlider"
        id: emotionSlider
        x: 39
        y: 62
        onValueChanged:{
            audioSlider.value = 1 - emotionSlider.value
        }
    }

    Label{
        x: 132
        y: 136
        text: "Audio"
    }
    Slider{
        objectName: "audioSlider"
        id: audioSlider
        x: 45
        y: 165
        onValueChanged:{
            emotionSlider.value = 1 - audioSlider.value
        }
    }

}
