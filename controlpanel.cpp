#include "controlpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

controlPanel::controlPanel(QWidget *parent) :
    QWidget(parent),
    _playPauseButton(new QPushButton("Play/Pause")),
    _nextButton(new QPushButton("Next")),
    _previousButton(new QPushButton("Previous")),
    _volumeSlider(new QSlider(Qt::Horizontal))
{
    _volumeSlider->setRange(0,100);
    _volumeSlider->setValue(50);

    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    QHBoxLayout * optionsLayout = new QHBoxLayout;

    buttonLayout->addWidget(_previousButton);
    buttonLayout->addWidget(_playPauseButton);
    buttonLayout->addWidget(_nextButton);

    optionsLayout->addWidget(_volumeSlider);

    layout->addLayout(optionsLayout);
    layout->addLayout(buttonLayout);

    this->setLayout(layout);
}

const QObject * controlPanel::widget(Widget widget)
{
    if(widget == controlPanel::PlayPauseButton)
        return _playPauseButton;
    else if(widget == controlPanel::NextButton)
        return _nextButton;
    else if(widget == controlPanel::PreviousButton)
        return _previousButton;
    else if(widget == controlPanel::VolumeSlider)
        return _volumeSlider;
    else return new QObject;
}
