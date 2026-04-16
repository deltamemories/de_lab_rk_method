#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "solverWrapper.h"
#include <iostream>
#include <string>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    SolverWrapper solverWrapper;
    engine.rootContext()->setContextProperty("solverWrapper", &solverWrapper);

    const QUrl url(QStringLiteral("qrc:/qt/qml/de_lab_rk_method/main.qml"));
    engine.load(url);

    return app.exec();
}
