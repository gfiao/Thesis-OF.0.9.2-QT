import QtQuick 2.5
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
            id: series1
            axisX: axisX
            axisY: axisY
        }

        LineSeries{
            id: series2
        }

    }

    function populateChart(emotionsX, emotionsY, maxX, maxY, tickCountX){
        axisX.max = maxX;
        axisY.max = maxY + 1;
       // axisX.tickCount = tickCountX;

        series1.append(emotionsX, emotionsY);
    }

}





