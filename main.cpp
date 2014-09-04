#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <exception>
using std::exception;

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        a.setStyle(QStyleFactory::create("Fusion"));

        MainWindow w;

        w.show();

        return a.exec();
    }
    catch(exception &e)
    {
        qDebug() << e.what();
        return 0;
    }
}
