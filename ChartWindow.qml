import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtCharts 2.1

Window {
    visible: false
    objectName: "chartWindow"
    id: chartWindow
    title: "Emotions Over Time"

    minimumWidth: 335
    minimumHeight: 250

    ChartView {
        title: "Emotions Over Time"
        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            titleText: "Timestamps (seconds)"
            id: axisX
            objectName: "axisX"
            min: 0
            //tickCount: 100
        }

        ValueAxis {
            titleText: "Number of Shared Emotions"
            id: axisY
            objectName: "axisY"
            min: 0
        }

        LineSeries {
            name: "Emotions"
            id: series1
            axisX: axisX
            axisY: axisY
        }

        ValueAxis{
            titleText: "Audio Values"
            id: audioY
        }

        LineSeries{
            name: "Audio"
            id: series2
            visible: false
            axisY: audioY
        }

    }
    Button{
        id: audioLine
        text: "Show Audio Values"

        onClicked: {
            if(series2.visible)
                series2.visible = false
            else series2.visible = true
        }
    }

    function populateChart(emotionsX, emotionsY, maxX, maxY){
        axisX.max = maxX;
        axisY.max = maxY + 1;

        series1.append(emotionsX, emotionsY);
    }

    function populateAudio(x, y, maxY){
        audioY.max = maxY;

        series2.append(x, y);
    }

}





