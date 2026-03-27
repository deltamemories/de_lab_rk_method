#ifndef DE_LAB_RK_METHOD_SOLVER_H
#define DE_LAB_RK_METHOD_SOLVER_H
#include <functional>


class Solver {
    std::function<double(double, double)> func;



public:
    Solver();
    double getNextYI(double yI, double xI, double h) const;
};



#endif //DE_LAB_RK_METHOD_SOLVER_H
