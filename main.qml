import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtGraphs

import de_lab_rk_method

Window {
    width: 350
    height: 500
    visible: true
    title: "RK method"

    SolverWrapper {
        id: backend
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: x0
                text: "x0"
                Layout.preferredWidth: 100
            }

            TextField {
                id: y0

                Layout.preferredWidth: 100
                text: "y0"
            }

            TextField {
                id: xEnd

                Layout.preferredWidth: 100
                text: "xEnd"
            }

            TextField {
                id: h

                Layout.preferredWidth: 100
                text: "h"
            }

            Button {
                text: "Draw"
                highlighted: true
                onClicked: {
                    let data = backend.solveFromQml(
                        parseFloat(x0.text),
                        parseFloat(y0.text),
                        parseFloat(xEnd.text),
                        parseFloat(h.text)
                    )
                    lineSeries.clear()
                    for (let i=0; i < data.length; i++) {
                        lineSeries.append(data[i].x, data[i].y)
                    }

                }
            }
        }

    GraphsView {
        Layout.fillWidth: true
        Layout.fillHeight: true

        axisX: ValueAxis {
            min: 0
            max: 10
            labelFormat: "%.1f"
        }

        axisY: ValueAxis {
            min: -5
            max: 5
            labelFormat: "%.1f"
        }

        

        LineSeries {
            id: lineSeries
            width: 2
            color: "red"
        }
    }


    }


}
