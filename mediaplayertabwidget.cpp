#include "mediaplayertabwidget.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QMediaContent>
#include <QDebug>

mediaPlayerTabWidget::mediaPlayerTabWidget(QWidget *parent) :
    QWidget(parent),
    _tabs(new QTabWidget),
    _metaData(new QLabel("Metadata will show up here as available.")),
    _players(new QList<basePlayer *>),
    _currentlyPlayingPlayer(new basePlayer),
    _controlPanel(NULL),
    _lyricsBox(NULL)
{
    QVBoxLayout * layout = new QVBoxLayout;

    _players->push_back(_currentlyPlayingPlayer);
    _tabs->addTab(_currentlyPlayingPlayer,"Playlist " + QString::number(_tabs->count()+1));

    connect(_currentlyPlayingPlayer, SIGNAL(metaDataChanged(QString,QString)), this, SLOT(newMetaDataReceived(QString,QString)));
    connect(_currentlyPlayingPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playerStateHasChanged(QMediaPlayer::State)));

    layout->addWidget(_tabs);
    layout->addWidget(_metaData);
    this->setLayout(layout);
}

bool mediaPlayerTabWidget::addMedia(const QStringList *filenames)
{
    const QList<QMediaContent> media = *basePlayer::getMediaContentFromFilePaths(filenames);
    return _players->at(_tabs->currentIndex())->addMedia(media);
}

bool mediaPlayerTabWidget::openMedia(const QStringList *filenames)
{
    const QList<QMediaContent> media = *basePlayer::getMediaContentFromFilePaths(filenames);
    return false;
}

void mediaPlayerTabWidget::setControlPanel(controlPanel * panel)
{
    _controlPanel = panel;
    connect(_controlPanel->widget(controlPanel::PlayPauseButton), SIGNAL(clicked()), this, SLOT(togglePlayPause()));
    connect(_controlPanel->widget(controlPanel::NextButton), SIGNAL(clicked()), this, SLOT(next()));
    connect(_controlPanel->widget(controlPanel::PreviousButton), SIGNAL(clicked()), this, SLOT(previous()));
    connect(_controlPanel->widget(controlPanel::VolumeSlider), SIGNAL(sliderMoved(int)), this, SLOT(setVolume(int)));
}

void mediaPlayerTabWidget::setLyricBox(lyricBox * lyricsBox)
{
    _lyricsBox = lyricsBox;
}

void mediaPlayerTabWidget::newMetaDataReceived(const QString &artist, const QString &title)
{
    if(QObject::sender() == _currentlyPlayingPlayer)
    {
        if(title.size())
        {
            if(artist.size())
                _metaData->setText(artist + " - " + title);
            else _metaData->setText(title);
        }
        else _metaData->setText("No Metadata Available.");

        if(_lyricsBox != NULL) _lyricsBox->getLyrics(artist, title);
    }
}

void mediaPlayerTabWidget::togglePlayPause()
{
    if(_currentlyPlayingPlayer == _players->at(_tabs->currentIndex()))
        _currentlyPlayingPlayer->togglePlayPause();
    else
    {
        //If we're not viewing playlist that is playing.
    }
}

void mediaPlayerTabWidget::next()
{
    _currentlyPlayingPlayer->next();
}

void mediaPlayerTabWidget::previous()
{
    _currentlyPlayingPlayer->previous();
}

void mediaPlayerTabWidget::setVolume(int volume)
{
    _currentlyPlayingPlayer->setVolume(volume);
}

void mediaPlayerTabWidget::playerStateHasChanged(QMediaPlayer::State state)
{
    if(_controlPanel != NULL)
    {
        if(state == QMediaPlayer::PausedState || state == QMediaPlayer::StoppedState)
            _controlPanel->setState(controlPanel::Paused);
        else if(state == QMediaPlayer::PlayingState)
            _controlPanel->setState(controlPanel::Playing);
    }
}
