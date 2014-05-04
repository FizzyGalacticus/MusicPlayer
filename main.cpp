#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QHBoxLayout>
#include <QtGui>
#include <QWidget>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
