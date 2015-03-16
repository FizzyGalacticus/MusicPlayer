#include "progressbar.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QDebug>

progressBar::progressBar(QWidget *parent) :
    QWidget(parent),
    _progressBar(new QProgressBar)
{
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(_progressBar);

    _progressBar->setMinimum(0);
    _progressBar->setMaximum(0);
    _progressBar->setTextVisible(false);

    this->setLayout(layout);
}

progressBar::~progressBar()
{

}

void progressBar::setProgressBarValue(qint64 value)
{
    _progressBar->setValue(value);
}

void progressBar::setProgressBarMaximum(qint64 maximum)
{
    _progressBar->setMaximum(maximum);
}

void progressBar::progressBarValueChanged(int value)
{
    emit valueChanged(value);
}

void progressBar::mousePressEvent(QMouseEvent * event)
{
    int value = ((_progressBar->maximum()*event->x())/this->width());
    _progressBar->setValue(value);
    emit valueChanged(value);
}

void progressBar::mouseMoveEvent(QMouseEvent * event)
{
    mousePressEvent(event);
}
