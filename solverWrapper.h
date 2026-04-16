#ifndef DE_LAB_RK_METHOD_SOLVERWRAPPER_H
#define DE_LAB_RK_METHOD_SOLVERWRAPPER_H


#include <QObject>
#include <qpoint.h>
#include <QVariantList>
#include <QPointF>
#include <QtQml/qqmlregistration.h>

#include "solver.h"

class SolverWrapper : public QObject {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit SolverWrapper(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE static QVariantList solveFromQml(double x0, double y0, double xEnd, double h) {
        const Solver solver;
        std::vector<Point> rawPoints = solver.solve(x0, y0, xEnd, h);
        QVariantList result;

        for (const Point& point : rawPoints) {
            result.append(QPointF(point.x, point.y));
        }

        return result;
    }

    Q_INVOKABLE static QVariantList solveFromQmlEps(double x0, double y0, double xEnd, double h, double eps) {
        const Solver solver;
        std::vector<Point> rawPoints = solver.solveWithDynamicStep(x0, y0, xEnd, h, eps);
        QVariantList result;
        for (const Point& point : rawPoints) {
            result.append(QPointF(point.x, point.y));
        }
        return result;
    }

    Q_INVOKABLE static QVariantList getRef(double x0, double y0, double xEnd, double h) {
        const Solver solver;
        std::vector<Point> rawPoints = solver.getRef(x0, y0, xEnd, h);
        QVariantList result;
        for (const Point& point : rawPoints) {
            result.append(QPointF(point.x, point.y));
        }
        return result;
    }
};



#endif //DE_LAB_RK_METHOD_SOLVERWRAPPER_H
