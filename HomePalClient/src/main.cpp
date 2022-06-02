#include <csignal>
#include <QDir>
#include <functional>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLockFile>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include "guicontroller.h"
#include <memory>

int main(int argc, char *argv[])
{
    int res = 0;
    try{
        QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
        QGuiApplication::setOrganizationName(QStringLiteral("bvovc"));
        QGuiApplication::setApplicationName(QStringLiteral("Home Pal Client"));
        QGuiApplication app(argc, argv);
        GUI_Controller c(&app);
        res = QGuiApplication::exec();
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception! " << ex.what();
        res = 1;
    }
    qDebug() << "main() END"<<"res:"<<res;
    return res;
}

