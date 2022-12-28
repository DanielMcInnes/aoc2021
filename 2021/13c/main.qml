import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ChartView {
        title: "Scatters"
        anchors.fill: parent
        antialiasing: true

        ScatterSeries {
            id: scatter1
            name: "Scatter1"
            XYPoint { x: 1.5; y: 1.5 }
            XYPoint { x: 1.5; y: 1.6 }
            XYPoint { x: 1.57; y: 1.55 }
            XYPoint { x: 1.8; y: 1.8 }
            XYPoint { x: 1.9; y: 1.6 }
            XYPoint { x: 2.1; y: 1.3 }
            XYPoint { x: 2.5; y: 2.1 }
        }
    }
}
