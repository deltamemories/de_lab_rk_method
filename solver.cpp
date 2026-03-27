#include "solver.h"
#include <cmath>

// x = [1, 2]; h=0.1; y(1) = -0.541325

double f(double x, double y) {
    return std::exp(y/x) + y/x + 1;
}

double testF(double x, double y) {
    return y;
}

Solver::Solver() {
    func = f;
}




double Solver::getNextYI(const double xI, const double yI, const double h) const {
    const double k1 = func(xI, yI);
    const double k2 = func(xI + 0.5*h, yI + 0.5*h*k1);
    const double k3 = func(xI + 0.5*h, yI + 0.5*h*k2);
    const double k4 = func(xI + h, yI + h*k3);
    const double yIPlus1 = yI + (1/6.0)*h*(k1 + 2*k2 + 2*k3 + k4);
    return yIPlus1;
}

bool Solver::rungeRule(const double yIH, const double yIHDividedBy2, const double epsilon) {
    return  1/15.0 * std::abs(yIH - yIHDividedBy2) < epsilon;
}


std::vector<Point> Solver::solve(const double x0, const double y0, const double xEnd, const double h) const {
    double xI = x0;
    double yI = y0;
    std::vector<Point> points;

    const int steps = static_cast<int>((xEnd-x0)/h);
    points.reserve(steps + 1);

    for (int i = 0; i <= steps; ++i) {
        points.push_back(Point(xI, yI)); // on first iter push (x0, y0) to vector

        yI = getNextYI(xI, yI, h); // get y_i+1
        xI = x0 + i*h; // get x_i+1
    }

    return points;
}
