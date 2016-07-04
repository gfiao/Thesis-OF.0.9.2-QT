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

    minimumWidth: 800
    minimumHeight: 400

    ChartView {
        title: "Emotions Over Time"
        objectName: "chart"
        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            titleText: "Timestamps (seconds)"
            id: axisX
            objectName: "axisX"
            min: 0
        }

        ValueAxis {
            titleText: "Number of Shared Emotions"
            id: axisY
            objectName: "axisY"
            min: 0
        }

        LineSeries {
            name: "Emotions"
            objectName: "emotionsLine"
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
            objectName: "audioLine"
            id: series2
            //visible: false
            axisY: audioY
        }

    }

    ColumnLayout{
        spacing: 8
        Item { Layout.preferredHeight: 4 } // padding

        Button{
            id: audioLine
            text: "Hide Audio Values"
            // x: 5
            // y: 5

            onClicked: {
                if(series2.visible)
                    series2.visible = false
                else series2.visible = true
            }
        }

        RowLayout{
            Label{
                text: "Interval: "
                font.bold: true
            }

            Slider{
                id: chartInterval
                objectName: "chartInterval"
                stepSize: 5
                minimumValue: 5
                maximumValue: 100
                // x: audioLine.x
                //y: audioLine.y + 5
                value: 30

                signal chartSignal(var msg)
                onValueChanged: chartInterval.chartSignal(value)
            }
        }
    }

    function clearSeries(){
        series1.clear();
        series2.clear();
    }

    function populateChart(emotionsX, emotionsY, maxX, maxY){
        axisX.max = maxX;
        axisY.max = maxY;

        series1.append(emotionsX, emotionsY);
    }

    function populateAudio(x, y, maxY){
        audioY.max = maxY;
        if(axisY.max < audioY.max)
            axisY.max = maxY;

        series2.append(x, y);
    }

}





