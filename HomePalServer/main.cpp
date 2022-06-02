#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/guicontroller.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    int res = 0;
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);

    QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QGuiApplication::setOrganizationName(QStringLiteral("bvovc"));
    QGuiApplication::setApplicationName(QStringLiteral("Home Pal Client"));
    //QGuiApplication app(argc, argv);
    GUI_Controller c(&app);
    res = QGuiApplication::exec();

//   engine.load(url);

    return app.exec();
}
