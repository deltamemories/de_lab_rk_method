#ifndef DE_LAB_RK_METHOD_MAINWINDOW_H
#define DE_LAB_RK_METHOD_MAINWINDOW_H

#include <QWidget>
#include "qcustomplot.h"
#include "solver.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void on_solveButton_clicked();
    void on_refButton_clicked();
    void on_clearButton_clicked();


private:
    Ui::MainWindow *ui;

    void setupPlot();
    void setupTable();
};


#endif //DE_LAB_RK_METHOD_MAINWINDOW_H
