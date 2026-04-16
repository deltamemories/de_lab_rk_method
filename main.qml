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
                        let data = backend.solveFromQml(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text));
                        let dataRef = backend.getRef(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text));
                        scatterSeries.clear();
                        tableModel.clear();

                        for (let i = 0; i < data.length; i++) {
                            scatterSeries.append(data[i].x, data[i].y);
                            if (i === 0) {
                                tableModel.append({
                                    "xI": data[i].x.toFixed(4),
                                    "yI": data[i].y.toFixed(8),
                                    "ref": dataRef[i].y.toFixed(8),
                                    "diff": Math.abs(dataRef[i].y.toFixed(4) - data[i].y).toFixed(8),
                                    "deltaY": "-"
                                });
                            } else {
                                tableModel.append({
                                    "xI": data[i].x.toFixed(4),
                                    "yI": data[i].y.toFixed(8),
                                    "deltaY": (Math.abs(data[i].y - data[i - 1].y)).toFixed(4),
                                    "ref": dataRef[i].y.toFixed(8),
                                    "diff": Math.abs(dataRef[i].y.toFixed(4) - data[i].y).toFixed(8)
                                });
                            }
                        }
                    }
                }
                Button {
                    id: drawButtonEps

                    text: "Draw with eps"

                    onClicked: {
                        let data = backend.solveFromQmlEps(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text), parseFloat(eps.text));
                        scatterSeriesEps.clear();
                        for (let i = 0; i < data.length; i++) {
                            scatterSeriesEps.append(data[i].x, data[i].y);
                        }
                    }
                }
                Button {
                    id: drawRef

                    text: "Draw ref"

                    onClicked: {
                        let dataRef = backend.getRef(parseFloat(x0.text), parseFloat(y0.text), parseFloat(xEnd.text), parseFloat(h.text));
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
                    anchors.centerIn: parent
                    height: width
                    width: Math.min(parent.width, parent.height)

                    axisX: ValueAxis {
                        labelFormat: "%.1f"
                        max: 5
                        min: 0
                    }
                    axisY: ValueAxis {
                        labelFormat: "%.1f"
                        max: 5
                        min: -5
                    }

                    ScatterSeries {
                        id: scatterSeries

                        pointDelegate: Rectangle {
                            color: "red"
                            height: 12
                            radius: width / 2
                            width: 12
                        }
                    }
                    ScatterSeries {
                        id: scatterSeriesEps

                        pointDelegate: Rectangle {
                            color: "blue"
                            height: 12
                            radius: width / 2
                            width: 12
                        }
                    }
                    LineSeries {
                        id: lineSeriesRef

                        color: "#00ff00"
                        width: 4
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
}
