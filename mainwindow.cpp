// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupTable();
    setupPlot();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupPlot() {
    ui->plot->addGraph();
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setName("Метод РК 4-го порядка");


    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    ui->plot->graph(1)->setName("Точное решение");

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRangeLower(0);

    ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    ui->plot->legend->setVisible(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(ui->plot->xAxis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged), [this](const QCPRange &newRange) {
        if (newRange.lower < 0) {
            double width = newRange.size();

            ui->plot->xAxis->blockSignals(true);
            ui->plot->xAxis->setRange(0, width);
            ui->plot->xAxis->blockSignals(false);

            ui->plot->replot();
        }
    });
}

void MainWindow::setupTable() {
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"x", "РК4", "Аналитика", "Погрешность"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

void MainWindow::on_solveButton_clicked() {
    double x0 = ui->x0Edit->text().toDouble();
    double y0 = ui->y0Edit->text().toDouble();
    double xEnd = ui->xEndEdit->text().toDouble();
    double h = ui->hEdit->text().toDouble();
    double eps = ui->epsEdit->text().toDouble();

    Solver solver;
    std::vector<PairedPoints> data = solver.solverWithDynamicStepPaired(x0, y0, xEnd, h, eps);

    QVector<double> x, yRK, yRef;
    for (const auto& p : data) {
        x.push_back(p.x);
        yRK.push_back(p.y);
        yRef.push_back(p.yRef);
    }

    ui->plot->graph(0)->setData(x, yRK);
    // ui->plot->graph(1)->setData(x, yRef);

    ui->plot->rescaleAxes();
    if (ui->plot->xAxis->range().lower < 0) {
        ui->plot->xAxis->setRangeLower(0);
    }
    ui->plot->replot();

    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < data.size(); ++i) {
        const auto& p = data[i];
        double error = std::abs(p.y - p.yRef);

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(p.x, 'g', 6)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(p.y, 'g', 6)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(p.yRef, 'g', 6)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(error, 'e', 3)));
    }

}

void MainWindow::on_refButton_clicked() {
    double x0 = ui->x0Edit->text().toDouble();
    double y0 = ui->y0Edit->text().toDouble();
    double xEnd = ui->xEndEdit->text().toDouble();
    double h = ui->hEdit->text().toDouble();
    double eps = ui->epsEdit->text().toDouble();

    Solver solver;
    std::vector<PairedPoints> data = solver.solverWithDynamicStepPaired(x0, y0, xEnd, h, eps);

    QVector<double> x, yRK, yRef;
    for (const auto& p : data) {
        x.push_back(p.x);
        yRK.push_back(p.y);
        yRef.push_back(p.yRef);
    }

    // ui->plot->graph(0)->setData(x, yRK);
    ui->plot->graph(1)->setData(x, yRef);

    ui->plot->rescaleAxes();
    if (ui->plot->xAxis->range().lower < 0) {
        ui->plot->xAxis->setRangeLower(0);
    }
    ui->plot->replot();
}

void MainWindow::on_clearButton_clicked() {
    ui->plot->graph(0)->data()->clear();
    ui->plot->graph(1)->data()->clear();
    ui->plot->replot();

    ui->plot->graph(0)->data()->clear();
    ui->plot->graph(1)->data()->clear();
    ui->plot->replot();

    ui->tableWidget->setRowCount(0);
}
