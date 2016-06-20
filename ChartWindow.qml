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
            id: axisX
            min: 0
            max: 900
            //tickCount: 5*/
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 10
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
        }
        // Add data dynamically to the series

    }

    function populateChart(x, y){
        series1.append(x, y);
        return x + " : " + y
    }


    /* Component.onCompleted: {
        for (var i = 0; i <= 10; i++) {
            series1.append(i, Math.random());
        }
    }*/
}





