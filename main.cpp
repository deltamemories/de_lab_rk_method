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
    std::vector<Point> solve = solver.solve(1, -0.541325, 2, 0.1);
    for (int i = 0; i < solve.size(); i++) {
        std::cout << solve[i].x << " " << solve[i].y << std::endl;
    }
}
