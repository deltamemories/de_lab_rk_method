#include <QApplication>
#include <QPushButton>

// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     QPushButton button("Hello world!", nullptr);
//     button.resize(200, 100);
//     button.show();
//     return QApplication::exec();
// }


#include <iostream>

#include "solver.h"

int main(int argc, char *argv[]) {
    Solver solver = Solver();
    double yIPlus1 = solver.getNextYI(2.0138, 0.7, 0.1);
    std::cout << yIPlus1 << std::endl;
}
