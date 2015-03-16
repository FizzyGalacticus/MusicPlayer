#include "progressbar.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QSpacerItem>

progressBar::progressBar(QWidget *parent) :
    QWidget(parent),
    _progressBar(new QProgressBar)
{
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(_progressBar);

    //DEBUG
    _progressBar->setMinimum(0);
    _progressBar->setMaximum(100);
    _progressBar->setValue(50);
    //

    this->setLayout(layout);
}

progressBar::~progressBar()
{

}

void progressBar::progressBarValueChanged(int value)
{
    emit valueChanged(value);
}

void progressBar::mousePressEvent(QMouseEvent * event)
{
    int value = (_progressBar->maximum()*event->x())/this->width();
    _progressBar->setValue(value);
}

void progressBar::mouseMoveEvent(QMouseEvent * event)
{
    mousePressEvent(event);
}
