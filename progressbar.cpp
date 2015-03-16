#include "progressbar.h"
#include <QVBoxLayout>

progressBar::progressBar(QWidget *parent) :
    QWidget(parent),
    _progressBar(new QProgressBar)
{
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(_progressBar);

    this->setLayout(layout);
}

progressBar::~progressBar()
{

}

