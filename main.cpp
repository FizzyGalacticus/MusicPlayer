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

    w.setMinimumHeight(2*72);
    w.setMinimumWidth(4*72);
    w.setMaximumHeight(8*72);
    w.setMaximumWidth(8*72);

    w.setObjectName("Music Player");

    w.show();

    return a.exec();
}
