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
    func = testF;
}


double Solver::getNextYI(const double yI, const double xI, const double h) const {
    const double k1 = func(xI, yI);
    const double k2 = func(xI + 0.5*h, yI + 0.5*h*k1);
    const double k3 = func(xI + 0.5*h, yI + 0.5*h*k2);
    const double k4 = func(xI + h, yI + h*k3);
    const double yIPlus1 = yI + (1/6.0)*h*(k1 + 2*k2 + 2*k3 + k4);
    return yIPlus1;
}
