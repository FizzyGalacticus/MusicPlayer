#include "basePlayer.h"
#include <QHBoxLayout>
#include <QtMultimedia/QMediaContent>
#include <QList>
#include <QStringList>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QDebug>

basePlayer::basePlayer(QWidget *parent) :
    QWidget(parent),
    _basePlayerView(new QListWidget),
    _player(new QMediaPlayer),
    _currentlyPlayingArtist(""),
    _currentlyPlayingTitle("")
{
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(_basePlayerView);
    this->setLayout(layout);

    _player->setPlaylist(new QMediaPlaylist);
    _player->setVolume(50);
    connect(_player->playlist(), SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexHasChanged(int)));
    connect(_player, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(metaDataAvailablityHasChanged(bool)));
}

bool basePlayer::clear()
{
    _basePlayerView->clear();
    return _player->playlist()->clear();
}

bool basePlayer::addMedia(const QList<QMediaContent> &items)
{
    _player->playlist()->addMedia(items);

    for(QList<QMediaContent>::const_iterator i = items.begin(); i < items.end(); i++)
        _basePlayerView->addItem(i->canonicalUrl().fileName());

    if(items.size() && items.size() == _player->playlist()->mediaCount())
    {
        _player->playlist()->setCurrentIndex(0);
        _basePlayerView->item(0)->setTextColor("red");
        return true;
    }
    else return false;
}

bool basePlayer::addMedia(const QMediaContent &content)
{
    QList<QMediaContent> contentList;
    contentList.push_back(content);

    return addMedia(contentList);
}

void basePlayer::togglePlayPause()
{
    if(_player->state() == QMediaPlayer::PausedState || _player->state() == QMediaPlayer::StoppedState)
    {
        _player->play();
        emit stateChanged(_player->state());
    }
    else if(_player->state() == QMediaPlayer::PlayingState)
    {
        _player->pause();
        emit stateChanged(_player->state());
    }
}

void basePlayer::next()
{
    if(_player->playlist()->playbackMode() == QMediaPlaylist::Loop || _player->playlist()->currentIndex() != _player->playlist()->mediaCount()-1)
        _player->playlist()->next();
}

void basePlayer::previous()
{
    if(_player->playlist()->playbackMode() == QMediaPlaylist::Loop || _player->playlist()->currentIndex() != 0)
        _player->playlist()->previous();
}

void basePlayer::setVolume(int volume)
{
    _player->setVolume(volume);
}

void basePlayer::currentIndexHasChanged(int index)
{
    for(int i = 0; i < _basePlayerView->count(); i++)
        _basePlayerView->item(i)->setTextColor("black");
    if(index > -1) _basePlayerView->item(index)->setTextColor("red");
    else if(_basePlayerView->count()) _basePlayerView->item(0)->setTextColor("red");
}

void basePlayer::metaDataAvailablityHasChanged(bool isMetaDataAvailable)
{
    if(isMetaDataAvailable)
    {
        if(_player->availableMetaData().contains("AlbumArtist"))
            _currentlyPlayingArtist = _player->metaData("AlbumArtist").toString();
        if(_player->availableMetaData().contains("Title"))
            _currentlyPlayingTitle = _player->metaData("Title").toString();
    }
    else
    {
        _currentlyPlayingArtist = "";
        _currentlyPlayingTitle = "";
    }

    emit metaDataChanged(_currentlyPlayingArtist, _currentlyPlayingTitle);
}
