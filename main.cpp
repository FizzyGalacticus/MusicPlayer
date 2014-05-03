#include "mainwindow.h"
#include <QApplication>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   /* w.setMinimumHeight(2*72);
    w.setMinimumWidth(4*72);
    w.setMaximumHeight(2*72);
    w.setMaximumWidth(4*72);*/
    w.setLayout(new QLayout);
    w.show();

    return a.exec();
}
