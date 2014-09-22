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

#ifdef __ANDROID__
        a.setStyleSheet("QScrollBar:horizontal {min-height:30} QScrollBar:vertical {min-width:30} QCheckBox::indicator {min-width:30px; min-height: 30px;}");
#endif

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
