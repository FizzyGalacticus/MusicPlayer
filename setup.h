#ifndef SETUP_H
#define SETUP_H

#include "mainwindow.h"
#include <QHBoxLayout>

void MainWindow::setupButtons()
{
    QHBoxLayout * buttons = new QHBoxLayout;
    buttons->addWidget(_prevButton);
    buttons->addWidget(_playButton);
    buttons->addWidget(_nextButton);

    //Setup signals
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(_prevButtonIsPressed()));
    connect(_playButton, SIGNAL(clicked()), this, SLOT(_playButtonIsPressed()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(_nextButtonIsPressed()));

    //Setup icons
    _prevButton->setIcon(_prevButtonIcon);
    _prevButton->setIconSize(QSize(_prevButton->height(),_prevButton->height()));

    _playButton->setIcon(_playButtonPlayIcon);
    _playButton->setIconSize(QSize(_playButton->height(),_playButton->height()));

    _nextButton->setIcon(_nextButtonIcon);
    _nextButton->setIconSize(QSize(_nextButton->height(),_nextButton->height()));

    _mainLayout->addLayout(buttons);
}

void MainWindow::setupMenus()
{
    createActions();
    createMenus();
}

void MainWindow::setupMetadataLabel()
{
    QHBoxLayout * metadata = new QHBoxLayout;
    metadata->addWidget(_fileMetadata);
    _mainLayout->addLayout(metadata);
}

void MainWindow::setupProgressBar()
{
    QHBoxLayout * progBar = new QHBoxLayout;
    progBar->addWidget(_progressBar);

    _progressBar->setValue(0);

    _progressBar->setTextVisible(false);

    connect(_currentPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(playbackPositionChanged(qint64)));
    connect(_currentPlayer, SIGNAL(durationChanged(qint64)),this, SLOT(durationHasChanged(qint64)));

    _mainLayout->addLayout(progBar);
}

void MainWindow::setupPlaylistViewConnections(const QListWidget * playlistView)
{
    connect
            (
                playlistView,
                SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this,
                SLOT(playlistItemHasBeenClicked(QListWidgetItem*))
            );

    connect
            (
                playlistView,
                SIGNAL(itemActivated(QListWidgetItem*)),
                this,
                SLOT(resetPlaylistViewFunctionality(QListWidgetItem*))
            );

    connect
            (
                playlistView,
                SIGNAL(itemClicked(QListWidgetItem*)),
                this,
                SLOT(resetPlaylistViewFunctionality(QListWidgetItem*))
            );

    connect
            (
                playlistView,
                SIGNAL(itemPressed(QListWidgetItem*)),
                this,
                SLOT(resetPlaylistViewFunctionality(QListWidgetItem*))
            );
}

void MainWindow::setupPlaylistTabs()
{
    _playlistViews->push_back(_currentPlaylistView);
    setupPlaylistViewConnections(_playlistViews->at(_playlistViews->count()-1));

    _playlistTabs->addTab(_currentPlaylistView, "Playlist");
    _playlistTabs->setTabsClosable(true);

    connect(_playlistTabs,SIGNAL(tabCloseRequested(int)),this,SLOT(_tabCloseRequested(int)));
    connect(_playlistTabs,SIGNAL(currentChanged(int)),this,SLOT(_currentTabIndexHasChanged(int)));

    _players->push_back(_currentPlayer);
    _currentPlayer->setPlaylist(new QMediaPlaylist);

    _mainLayout->addWidget(_playlistTabs);
}

void MainWindow::setupOptionDash()
{
    QHBoxLayout * optionDash = new QHBoxLayout;
    optionDash->addWidget(_newPlaylistTabButton);
    optionDash->addWidget(_shuffleButton);
    optionDash->addWidget(_loopCheckbox);
    optionDash->addWidget(_volumeLabel);
    optionDash->addWidget(_volumeSlider);

    connect(_newPlaylistTabButton,SIGNAL(clicked()),this,SLOT(_newPlaylistTabButtonIsPressed()));

    connect(_shuffleButton,SIGNAL(clicked()),this,SLOT(_shuffleButtonHasBeenPressed()));

    _loopCheckbox->setText("Loop");
    connect(_loopCheckbox, SIGNAL(stateChanged(int)), this, SLOT(_loopCheckboxStateHasChanged(int)));

    _shuffleButton->setText("Shuffle");

    _volumeLabel->setText(tr("<b>Volume:</b>"));
    _volumeSlider->setRange(0,100);
    _volumeSlider->setSliderPosition(_currentPlayer->volume());
    connect(_volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(_volumeSliderValueChanged()));

    _mainLayout->addLayout(optionDash);
}

void MainWindow::setup()
{
    setupPlaylistTabs();
    setupProgressBar();
    setupMetadataLabel();
    setupMenus();
    setupOptionDash();
    setupButtons();
}

#endif // SETUP_H
