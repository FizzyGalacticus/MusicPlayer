#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    for(int i = 0; i < QStyleFactory::keys().size(); i++)
        qDebug() << QStyleFactory::keys()[i];

    MainWindow w;

    w.show();

    return a.exec();
}
