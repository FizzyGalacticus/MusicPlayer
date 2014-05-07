#ifndef SETUP_H
#define SETUP_H

#include "mainwindow.h"

void MainWindow::setupButtons()
{
    const int mediaButtonYCoordinate =
            (
                height()- ((width()/5) + 50) //statusBar()->geometry().height()
            );

    //Setup signals
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(_prevButtonIsPressed()));
    connect(_playButton, SIGNAL(clicked()), this, SLOT(_playButtonIsPressed()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(_nextButtonIsPressed()));

    //Setup positions
    _prevButton->setGeometry
            (
                0,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _playButton->setGeometry
            (
                _prevButton->width()*2,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _nextButton->setGeometry
            (
                _playButton->width()*4,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );

    //Setup icons
    _prevButton->setIcon(_prevButtonIcon);
    _prevButton->setIconSize(QSize(_prevButton->height(),_prevButton->height()));

    _playButton->setIcon(_playButtonPlayIcon);
    _playButton->setIconSize(QSize(_playButton->height(),_playButton->height()));

    _nextButton->setIcon(_nextButtonIcon);
    _nextButton->setIconSize(QSize(_nextButton->height(),_nextButton->height()));

    //Show them off
    _prevButton->show();
    _playButton->show();
    _nextButton->show();
}

void MainWindow::setupMenus()
{
    createActions();
    createMenus();
}

void MainWindow::setupMetadataLabel()
{
    _fileMetadata->setGeometry
            (
                0,
                _volumeLabel->geometry().y(),
                _shuffleCheckbox->geometry().x(),
                _volumeLabel->geometry().height()
            );

    _fileMetadata->show();
}

void MainWindow::setupProgressBar()
{
    _progressBar->setGeometry(0,28,width(),height()/3);
    _progressBar->setValue(0);
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(playbackPositionChanged(qint64)));
    connect(_player, SIGNAL(durationChanged(qint64)),this, SLOT(durationHasChanged(qint64)));
    _progressBar->show();
}

void MainWindow::setupShuffleCheckbox()
{
    connect(_shuffleCheckbox, SIGNAL(stateChanged(int)), this, SLOT(shuffleCheckboxHasChanged(int)));

    _shuffleCheckbox->setGeometry
            (
                _playButton->geometry().x(),
                _volumeLabel->geometry().y(),
                _volumeSlider->width()+10,
                _volumeLabel->height()
            );

    _shuffleCheckbox->show();
}

void MainWindow::setupVolumeLabelAndSlider()
{
    _volumeLabel->setText(tr("<b>Volume:</b>"));
    _volumeSlider->setRange(0,100);
    _volumeSlider->setSliderPosition(_player->volume());
    _volumeSlider->setGeometry
            (
                _nextButton->geometry().x(),
                _playButton->geometry().y()-20,
                _playButton->width(),
                20
            );
    _volumeLabel->setGeometry
            (
                _volumeSlider->geometry().x()-60,
                _volumeSlider->geometry().y(),
                60,
                _volumeSlider->height()
            );

    connect(_volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(_volumeSliderValueChanged()));

    _volumeLabel->show();
    _volumeSlider->show();
}

void MainWindow::setupPlaylistView()
{
    connect
            (
                _playlistView,
                SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this,
                SLOT(playlistItemHasBeenClicked(QListWidgetItem*))
            );

    _playlistView->setGeometry
            (
                0,
                _progressBar->y()+_progressBar->height(),
                width(),
                100
            );

    _playlistView->show();
}

void MainWindow::setup()
{
    setupButtons();
    setupMenus();
    setupProgressBar();
    setupVolumeLabelAndSlider();
    setupShuffleCheckbox();
    setupMetadataLabel();
    setupPlaylistView();
}

#endif // SETUP_H
