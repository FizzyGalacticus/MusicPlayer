#include "controlpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

controlPanel::controlPanel(QWidget *parent) :
    QWidget(parent),
    _playPauseButton(new QPushButton("Play/Pause")),
    _nextButton(new QPushButton("Next")),
    _previousButton(new QPushButton("Previous")),
    _volumeSlider(new QSlider(Qt::Horizontal)),
    _currentState(controlPanel::Paused)
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

void controlPanel::setPlayButtonIcon(const QIcon &icon)
{
    _playButtonIcon = icon;

    _playPauseButton->text().clear();

    if(_currentState == controlPanel::Paused)
        _playPauseButton->setIcon(icon);

}

void controlPanel::setPauseButtonIcon(const QIcon &icon)
{
    _pauseButtonIcon = icon;

    _playPauseButton->text().clear();

    if(_currentState == controlPanel::Playing)
        _playPauseButton->setIcon(icon);
}

void controlPanel::setNextButtonIcon(const QIcon &icon)
{
    _nextButton->text().clear();
    _nextButton->setIcon(icon);
}

void controlPanel::setPreviousButtonIcon(const QIcon &icon)
{
    _previousButton->text().clear();
    _previousButton->setIcon(icon);
}

void controlPanel::togglePlayPauseState()
{
    if(_currentState == controlPanel::Paused)
    {
        _currentState = controlPanel::Playing;
        if(!_playButtonIcon.isNull())
            _playPauseButton->setIcon(_pauseButtonIcon);
        else
        {
            _playPauseButton->setIcon(QIcon());
            _playPauseButton->setText("Pause");
        }
    }
    else if(_currentState == controlPanel::Playing)
    {
        _currentState = controlPanel::Paused;
        if(!_pauseButtonIcon.isNull())
            _playPauseButton->setIcon(_playButtonIcon);
        else
        {
            _playPauseButton->setIcon(QIcon());
            _playPauseButton->setText("Play");
        }
    }
}
