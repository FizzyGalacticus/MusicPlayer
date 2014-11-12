#ifndef SETUP_H
#define SETUP_H

#include "mainwindow.h"
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFont>

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

#ifdef __ANDROID__
    QHBoxLayout * androidButtonLayout = new QHBoxLayout(this);

    QPushButton * androidAddButton = new QPushButton("Add Music", this);
    //QPushButton * androidExitButton = new QPushButton("Exit", this);

    connect(androidAddButton, SIGNAL(clicked()), this, SLOT(menuAddMedia()));
    //connect(androidExitButton, SIGNAL(clicked()), this, SLOT(exit()));

    androidButtonLayout->addWidget(androidAddButton);
    //androidButtonLayout->addWidget(androidExitButton);

    _mainLayout->addLayout(androidButtonLayout);
#endif
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
    optionDash->addStretch();
    optionDash->addWidget(_shuffleButton);
    optionDash->addStretch();
    optionDash->addWidget(_loopCheckbox);
    optionDash->addStretch();
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

void MainWindow::setupLyricsWidget()
{
    QFont * comicSans = new QFont("Comic Sans MS",12);

    _lyricsTextBox->setFont(*comicSans);
    _lyricsTextBox->setText("If your song has the appropriate metadata (Artist & Song Title), the lyrics will show up here!");
    _lyricsTextBox->setReadOnly(true);

    _lyricsWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::NoDockWidgetArea);
    _lyricsWidget->setMinimumWidth(200);
    _lyricsWidget->setWidget(_lyricsTextBox);
    addDockWidget(Qt::RightDockWidgetArea,_lyricsWidget);
}

void MainWindow::setup()
{
    setupMenus();
    setupPlaylistTabs();
    setupProgressBar();
    setupMetadataLabel();
    setupOptionDash();
    setupButtons();
    setupLyricsWidget();

    if(QCoreApplication::arguments().size())
    {
        QStringList * arguments = new QStringList(QCoreApplication::arguments());
        arguments->removeFirst();
        addMedia(arguments);
    }

#ifdef __ANDROID__
    QList<QMediaContent> * myContent = new QList<QMediaContent>;
    QStringList * audioFiles = getAllMusicFiles(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory));

    for(int i = 0; i < audioFiles->count(); i++)
        myContent->push_back(QMediaContent(QUrl::fromLocalFile(audioFiles->at(i))));

    _currentPlayer->setPlaylist(new QMediaPlaylist);
    _currentPlayer->playlist()->addMedia(*myContent);
    _currentPlayer->playlist()->setCurrentIndex(0);
    _currentPlayer->playlist()->shuffle();
    _currentPlayer->setVolume(100);
    _loopCheckbox->setMinimumWidth(120);
    _volumeSlider->hide();
    _volumeLabel->hide();

    this->setMaximumSize(this->width(), this->height());

    refreshPlaylistView();

#endif
}

#endif // SETUP_H
