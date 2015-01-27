#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>

class controlPanel : public QWidget
{
    Q_OBJECT
public:
    enum Widget{ PreviousButton, PlayPauseButton, NextButton, VolumeSlider};
    explicit controlPanel(QWidget *parent = 0);

    const QObject * widget(controlPanel::Widget widget);

signals:

public slots:

private:
    QPushButton * _playPauseButton;
    QPushButton * _nextButton;
    QPushButton * _previousButton;

    QSlider * _volumeSlider;

};

#endif // CONTROLPANEL_H
