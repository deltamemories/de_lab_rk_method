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
    return y*y-2/(x*x);
}

double rf(double x) {
    return -1*x*std::log(std::numbers::e / x - 1);
}

double testRf(double x) {
    return 1/(-2/3.0*(1/(x*x))-x/3)+1/x;
}



Solver::Solver() {
    func = f;
    // func = testF;
    refFunc = rf;
    // refFunc = testRf;
    hMin = std::numeric_limits<double>::epsilon();
    maxAttemptsCount = 200;
    accuracyGrowCoefficientForIncrementStep = 100;
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


std::vector<Point> Solver::solve(const double x0, const double y0, const double xEnd, double h) const {
    double xI = x0;
    double yI = y0;

    std::vector<Point> points = {Point(xI, yI)};

    while (xI < xEnd) {
        // std::cout << "xI:" << xI << std::endl;
        if (xI+h>xEnd) {
            h = xEnd - xI;
        }

        yI = getNextYI(xI, yI, h); // get y_i+1
        xI = xI + h; // get x_i+1
        points.push_back(Point(xI, yI));
        // std::cout << "xIn:" << xI << std::endl;

        if (std::abs(xI - xEnd) < hMin) break;
    }

    return points;
}

std::vector<Point> Solver::getRef(double x0, double y0, double xEnd, double h) const {
    double xI = x0;
    double yI = y0;

    std::vector<Point> points = {};

    while (xI < xEnd) {
        // std::cout << "xI:" << xI << std::endl;
        if (xI+h>xEnd) {
            h = xEnd - xI;
        }

        yI = refFunc(xI);

        points.push_back(Point(xI, yI));
        xI = xI + h; // get x_i+1

        // std::cout << "xIn:" << xI << std::endl;

        if (std::abs(xI - xEnd) < hMin) break;
    }

    points.push_back(Point(xI, refFunc(xI)));


    for (int i = 0; i < points.size(); i++) {
        // std::cout << "REF " << i << " " << points[i].x << " " << points[i].y << std::endl;
    }

    return points;
}

std::vector<Point> Solver::solveWithDynamicStep(const double x0, const double y0, const double xEnd, double h, const double epsilon) const {
    double xI = x0;
    double yI = y0;
    std::vector points = {Point(xI, yI)};

    while (xI < xEnd) {
        if (xI + h > xEnd) {
            h = xEnd - xI;
        }
        // std::cout << "H:" << h << std::endl;

        double y = getNextYI(xI, yI, h);

        double yMid = getNextYI(xI, yI, h / 2.0);
        double yFinal = getNextYI(xI + h / 2.0, yMid, h / 2.0);

        double error = rungeRule(y, yFinal);

        // std::cout << error-epsilon << std::endl;
        if (error < epsilon) {
            xI += h;
            yI = yFinal;
            points.push_back(Point(xI, yI));
            // std::cout << "OK" << std::endl;
            if (error < epsilon / accuracyGrowCoefficientForIncrementStep) {
                h *= 2.0;
                // std::cout << "+" << std::endl;
            }
        } else {
            h /= 2.0;
            // std::cout << "-" << std::endl;

            if (h < hMin) {
                throw std::logic_error("Step is too small.");
            }
        }
    }

    return points;
}

std::vector<PairedPoints> Solver::solverWithDynamicStepPaired(double x0, double y0, double xEnd, double h, double epsilon) const {
    double xI = x0;
    double yI = y0;
    std::vector pairedPoints = {PairedPoints(xI, yI, yI)};

    while (xI < xEnd) {
        if (xI + h > xEnd) {
            h = xEnd - xI;
        }
        // std::cout << "H:" << h << std::endl;

        double y = getNextYI(xI, yI, h);

        double yMid = getNextYI(xI, yI, h / 2.0);
        double yFinal = getNextYI(xI + h / 2.0, yMid, h / 2.0);

        double error = rungeRule(y, yFinal);

        // std::cout << error-epsilon << std::endl;
        if (error < epsilon) {
            xI += h;
            yI = yFinal;
            const double yRef = refFunc(xI);
            pairedPoints.push_back(PairedPoints(xI, yI, yRef));
            // std::cout << "OK" << std::endl;
            if (error < epsilon / accuracyGrowCoefficientForIncrementStep) {
                h *= 2.0;
                // std::cout << "+" << std::endl;
            }
        } else {
            h /= 2.0;
            // std::cout << "-" << std::endl;

            if (h < hMin) {
                throw std::logic_error("Step is too small.");
            }
        }
    }

    return pairedPoints;
}
