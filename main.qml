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
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RowLayout {
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
                    scatterSeries.clear();
                    for (let i = 0; i < data.length; i++) {
                        scatterSeries.append(data[i].x, data[i].y);
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
                id: clearGraphs
                text: "clear"

                onClicked: {
                    scatterSeries.clear();
                    scatterSeriesEps.clear();
                }
            }
        }


        GraphsView {
            Layout.fillHeight: true
            Layout.fillWidth: true

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

                color: "red"
            }

            ScatterSeries {
                id: scatterSeriesEps

                color: "blue"
            }

            ScatterSeries {
                id: scatterSeriesRef

                color: "green"
            }
        }
    }
}
