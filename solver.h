#ifndef DE_LAB_RK_METHOD_SOLVER_H
#define DE_LAB_RK_METHOD_SOLVER_H
#include <functional>


struct Point {
    double x;
    double y;
};

class Solver {
    std::function<double(double, double)> func;
    std::function<double(double)> refFunc;
    double hMin;
    int maxAttemptsCount;
    double accuracyGrowCoefficientForIncrementStep;

public:
    Solver();
    [[nodiscard]] std::vector<Point> solve(double x0, double y0, double xEnd, double h) const;
    [[nodiscard]] std::vector<Point> solveWithDynamicStep(double x0, double y0, double xEnd, double h, double epsilon) const;
    [[nodiscard]] std::vector<Point> getRef(double x0, double y0, double xEnd, double h) const;

private:
    [[nodiscard]] double getNextYI(double xI, double yI, double h) const;

    [[nodiscard]] static double rungeRule(double yIH, double yIHDividedBy2);
};



#endif //DE_LAB_RK_METHOD_SOLVER_H
