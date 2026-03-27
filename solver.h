#ifndef DE_LAB_RK_METHOD_SOLVER_H
#define DE_LAB_RK_METHOD_SOLVER_H
#include <functional>


struct Point {
    double x;
    double y;
};

class Solver {
    std::function<double(double, double)> func;



public:
    Solver();
    [[nodiscard]] std::vector<Point> solve(double x0, double y0, double xEnd, double h) const;

private:
    [[nodiscard]] double getNextYI(double xI, double yI, double h) const;
    bool rungeRule(); // TODO
};



#endif //DE_LAB_RK_METHOD_SOLVER_H
