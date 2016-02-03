#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include "multimodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    qRegisterMetaType<SingleModel>("SingleModel");
//    qRegisterMetaType<MultiModel>("MultiModel");
    qmlRegisterType<BaseData>("CustomModel", 1, 0, "BaseData");
    qmlRegisterType<SingleModel>("CustomModel", 1, 0, "SingleModel");
    qmlRegisterType<MultiModel>("CustomModel", 1, 0, "MultiModel");

//    QQuickView view(QUrl("qrc:/main.qml"));
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
