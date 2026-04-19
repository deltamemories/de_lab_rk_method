import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtGraphs

import de_lab_rk_method

Window {
    height: 500
    title: "RK method"
    visible: true
    width: 350

    SolverWrapper {
        id: backend

    }
    ListModel {
        id: tableModel

    }
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 20

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 10

            Flow {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: x0

                    Layout.preferredWidth: 200
                    placeholderText: "x0"
                    text: "1"
                }
                TextField {
                    id: y0

                    Layout.preferredWidth: 200
                    placeholderText: "y0"
                    text: "-0.541325"
                }
                TextField {
                    id: xEnd

                    Layout.preferredWidth: 200
                    placeholderText: "xEnd"
                    text: "2"
                }
                TextField {
                    id: h

                    Layout.preferredWidth: 200
                    placeholderText: "h"
                    text: "0.1"
                }
                TextField {
                    id: eps

                    Layout.preferredWidth: 200
                    placeholderText: "eps"
                    text: "0.001"
                }
                Button {
                    id: drawButton

                    highlighted: true
                    text: "Draw"

                    onClicked: {
                        try {
                            let data = backend.solveFromQml(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text));
                            let dataRef = backend.getRef(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text));
                            scatterSeries.clear();
                            tableModel.clear();

                            for (let i = 0; i < data.length; i++) {
                                scatterSeries.append(data[i].x, data[i].y);
                                tableModel.append({
                                    "xI": data[i].x.toFixed(4),
                                    "yI": data[i].y.toFixed(8),
                                    "ref": dataRef[i].y.toFixed(8),
                                    "diff": Math.abs(dataRef[i].y - data[i].y).toExponential(4),
                                    "deltaY": i === 0 ? "-" : (Math.abs(data[i].y - data[i - 1].y)).toFixed(4)
                                });
                            }
                        } catch (err) {
                            errorLabel.text = err.message;
                            errorPopup.open();
                        }
                    }
                }
                Button {
                    id: drawButtonEps

                    text: "Draw with eps"

                    onClicked: {
                        try {
                            let data = backend.solveFromQmlEpsAndRef(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text), parseFloat(eps.text));
                            scatterSeriesEps.clear();
                            tableModel.clear();

                            for (let i = 0; i < data.length; i++) {
                                scatterSeriesEps.append(data[i].x, data[i].y);
                                tableModel.append({
                                    "xI": data[i].x.toFixed(4),
                                    "yI": data[i].y.toFixed(8),
                                    "ref": data[i].yRef.toFixed(8),
                                    "diff": Math.abs(data[i].yRef - data[i].y).toExponential(4),
                                    "deltaY": i === 0 ? "-" : (Math.abs(data[i].y - data[i - 1].y)).toFixed(4)
                                });
                            }
                        } catch (err) {
                            errorLabel.text = err.message;
                            errorPopup.open();
                        }
                    }
                }
                Button {
                    id: drawRef

                    text: "Draw ref"

                    onClicked: {
                        let dataRef = backend.getRef(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), 0.01);
                        lineSeriesRef.clear();
                        for (let i = 0; i < dataRef.length; i++) {
                            lineSeriesRef.append(dataRef[i].x, dataRef[i].y);
                        }
                    }
                }
                Button {
                    id: clearGraphs

                    text: "clear graphs"

                    onClicked: {
                        scatterSeries.clear();
                        scatterSeriesEps.clear();
                        lineSeriesRef.clear();
                    }
                }
                Button {
                    id: clearTable

                    text: "clear table"

                    onClicked: {
                        tableModel.clear();
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                GraphsView {
                    id: graphsView

                    function updateFakeAxes() {
                        fakeXAxis.clear();
                        fakeXAxis.append(xAxis.min, 0);
                        fakeXAxis.append(xAxis.max, 0);
                        fakeYAxis.clear();
                        fakeYAxis.append(0, yAxis.min);
                        fakeYAxis.append(0, yAxis.max);
                    }

                    anchors.centerIn: parent
                    height: width
                    width: Math.min(parent.width, parent.height)

                    axisX: ValueAxis {
                        id: xAxis

                        labelFormat: "%.1f"
                        max: 5
                        min: -5
                        titleText: "X"
                    }
                    axisY: ValueAxis {
                        id: yAxis

                        labelFormat: "%.1f"
                        max: 5
                        min: -5
                        titleText: "Y"
                    }
                    theme: GraphsTheme {
                        colorScheme: GraphsTheme.ColorScheme.Light
                    }

                    Component.onCompleted: updateFakeAxes()

                    ScatterSeries {
                        id: scatterSeries

                        name: "RK with fixed step"

                        pointDelegate: Rectangle {
                            color: "#bf0000"
                            height: 6
                            radius: width / 2
                            width: 6
                        }
                    }
                    ScatterSeries {
                        id: scatterSeriesEps

                        name: "RK with eps"

                        pointDelegate: Rectangle {
                            color: "#0000ff"
                            height: 6
                            radius: width / 2
                            width: 6
                        }
                    }
                    LineSeries {
                        id: lineSeriesRef

                        color: "#009600"
                        name: "reference"
                        width: 2
                    }
                    LineSeries {
                        id: fakeXAxis

                        color: "#000000"
                        width: 3
                    }
                    LineSeries {
                        id: fakeYAxis

                        color: "#000000"
                        width: 3
                    }
                    TapHandler {
                        onTapped: console.log("Graph clicked at coordinates:", point.position)
                    }
                    WheelHandler {
                        id: wheelHandler

                        target: null

                        onWheel: event => {
                            let zoomFactor = event.angleDelta.y > 0 ? 0.9 : 1.1;
                            let xRange = xAxis.max - xAxis.min;
                            let yRange = yAxis.max - yAxis.min;
                            let xCenter = (xAxis.max + xAxis.min) / 2;
                            let yCenter = (yAxis.max + yAxis.min) / 2;

                            xAxis.min = xCenter - (xRange * zoomFactor) / 2;
                            xAxis.max = xCenter + (xRange * zoomFactor) / 2;
                            yAxis.min = yCenter - (yRange * zoomFactor) / 2;
                            yAxis.max = yCenter + (yRange * zoomFactor) / 2;

                            graphsView.updateFakeAxes();
                        }
                    }
                    DragHandler {
                        id: dragHandler

                        property real startMaxX: 0
                        property real startMaxY: 0
                        property real startMinX: 0
                        property real startMinY: 0

                        acceptedButtons: Qt.LeftButton
                        target: null

                        onActiveChanged: {
                            if (active) {
                                startMinX = xAxis.min;
                                startMaxX = xAxis.max;
                                startMinY = yAxis.min;
                                startMaxY = yAxis.max;
                            }
                        }
                        onCentroidChanged: {
                            if (!active)
                                return;

                            let totalDxPixels = centroid.position.x - centroid.pressPosition.x;
                            let totalDyPixels = centroid.position.y - centroid.pressPosition.y;

                            let xFactor = (startMaxX - startMinX) / graphsView.width;
                            let yFactor = (startMaxY - startMinY) / graphsView.height;

                            let deltaX = totalDxPixels * xFactor;
                            let deltaY = totalDyPixels * yFactor;

                            xAxis.min = startMinX - deltaX;
                            xAxis.max = startMaxX - deltaX;

                            yAxis.min = startMinY + deltaY;
                            yAxis.max = startMaxY + deltaY;

                            graphsView.updateFakeAxes();
                        }
                    }
                }
            }
        }
        ColumnLayout {
            Layout.fillHeight: true
            Layout.preferredWidth: 500

            Rectangle {
                Layout.fillWidth: true
                color: "#eeeeee"
                height: 30

                Row {
                    anchors.fill: parent

                    Repeater {
                        model: ["xI", "deltaY", "yI", "ref", "diff"]

                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: modelData
                            width: parent.width / 5
                        }
                    }
                }
            }
            ListView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: tableModel

                delegate: Rectangle {
                    border.color: "#cccccc"
                    height: 30
                    width: parent.width

                    Row {
                        anchors.fill: parent

                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: model.xI
                            width: parent.width / 5
                        }
                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: model.deltaY
                            width: parent.width / 5
                        }
                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: model.yI
                            width: parent.width / 5
                        }
                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: model.ref
                            width: parent.width / 5
                        }
                        Label {
                            horizontalAlignment: Text.AlignHCenter
                            text: model.diff
                            width: parent.width / 5
                        }
                    }
                }
            }
        }
    }
    Popup {
        id: errorPopup

        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        focus: true
        height: 120
        modal: true
        width: 250

        background: Rectangle {
            border.color: "#bf0000"
            border.width: 2
            radius: 8
        }
        contentItem: ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Label {
                text: "Error"
            }
            Label {
                id: errorLabel
                text: ""
            }
        }
    }
}