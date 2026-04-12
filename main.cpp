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
#include <string>
#include "solver.h"

int main(int argc, char *argv[]) {
    const auto solver = Solver();

    std::string input = "";
    std::cin >> input;
    std::vector<Point> solve;
    if (input == "d") {
        solve = solver.solveWithDynamicStep(1, -0.541325, 2, 0.1, 0.000000000001);
    } else {
        solve = solver.solve(1, -0.541325, 2, 0.1);
    }

    for (int i = 0; i < solve.size(); i++) {
        std::cout << solve[i].x << " " << solve[i].y << std::endl;
    }
}
