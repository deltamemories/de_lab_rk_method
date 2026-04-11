#include "solver.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

// x = [1, 2]; h=0.1; y(1) = -0.541325

double f(double x, double y) {
    return std::exp(y/x) + y/x + 1;
}

double testF(double x, double y) {
    return y;
}

Solver::Solver() {
    func = f;
    hMin = std::numeric_limits<double>::epsilon();
    maxAttemptsCount = 200;
}




double Solver::getNextYI(const double xI, const double yI, const double h) const {
    const double k1 = func(xI, yI);
    const double k2 = func(xI + 0.5*h, yI + 0.5*h*k1);
    const double k3 = func(xI + 0.5*h, yI + 0.5*h*k2);
    const double k4 = func(xI + h, yI + h*k3);
    const double yIPlus1 = yI + (1/6.0)*h*(k1 + 2*k2 + 2*k3 + k4);
    return yIPlus1;
}

double Solver::rungeRule(const double yIH, const double yIHDividedBy2) {
    return  1/15.0 * std::abs(yIH - yIHDividedBy2);
}


std::vector<Point> Solver::solve(const double x0, const double y0, const double xEnd, const double h) const {
    double xI = x0;
    double yI = y0;

    std::vector<Point> points;

    while (xI < xEnd) {
        points.push_back(Point(xI, yI)); // on first iter push (x0, y0) to vector
        yI = getNextYI(xI, yI, h); // get y_i+1
        xI = xI + h; // get x_i+1
    }

    return points;
}

std::vector<Point> Solver::solveWithDynamicStep(const double x0, const double y0, const double xEnd, double h, const double epsilon) const {
    double xI = x0;
    double yI = y0;
    std::vector points = {Point(xI, yI)};

    int errorsCount = 0;
    while (xI < xEnd) {
        double y = getNextYI(xI, yI, h);

        double yMid = getNextYI(xI, yI, h / 2.0);
        double yFinal = getNextYI(xI + h / 2.0, yMid, h / 2.0);

        if (rungeRule(y, yFinal) < epsilon) {
            xI += h;
            yI = yFinal;
            points.push_back(Point(xI, yI));

            // step may be increased
        } else {
            h /= 2.0;

            if (h < hMin) {
                throw std::logic_error("Step is too small.");
            }
        }

        if (xI + h > xEnd) {
            h = xEnd - xI;
        }
    }

    return points;
}
