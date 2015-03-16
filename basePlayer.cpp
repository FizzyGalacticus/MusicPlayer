#include "basePlayer.h"
#include <QHBoxLayout>
#include <QtMultimedia/QMediaContent>
#include <QList>
#include <QStringList>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QAction>

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

    QAction * add = new QAction(tr("Add Media"),this);
    QAction * open = new QAction(tr("Open Media"),this);
    connect(add, SIGNAL(triggered()), this, SLOT(initiateAddMedia()));
    connect(open, SIGNAL(triggered()), this, SLOT(initiateOpenMedia()));

    _basePlayerView->addAction(add);
    _basePlayerView->addAction(open);

    _basePlayerView->setContextMenuPolicy(Qt::ActionsContextMenu);

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

bool basePlayer::openMedia(const QMediaContent &content)
{
    _player->stop();
    _player->playlist()->clear();

    return addMedia(content);
}

bool basePlayer::openMedia(const QList<QMediaContent> &items)
{
    _player->stop();
    _player->playlist()->clear();

    return addMedia(items);
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
    else if(_basePlayerView->count())_basePlayerView->item(0)->setTextColor("red");
}

void basePlayer::metaDataAvailablityHasChanged(bool isMetaDataAvailable)
{
    if(isMetaDataAvailable)
    {
        if(_player->availableMetaData().contains("AlbumArtist"))
            _currentlyPlayingArtist = _player->metaData("AlbumArtist").toString();
        if(_player->availableMetaData().contains("Title"))
        {
            _currentlyPlayingTitle = _player->metaData("Title").toString();
            removeFeaturingArtistFromTitle();
        }
    }
    else
    {
        _currentlyPlayingArtist = "";
        _currentlyPlayingTitle = "";
    }

    emit metaDataChanged(_currentlyPlayingArtist, _currentlyPlayingTitle);
}

void basePlayer::removeFeaturingArtistFromTitle()
{
    if(_currentlyPlayingTitle.contains("feat",Qt::CaseInsensitive))
        _currentlyPlayingTitle.remove(
                    _currentlyPlayingTitle.indexOf("feat",0,Qt::CaseInsensitive),
                    _currentlyPlayingTitle.size()-1
                    );
    do
    {
        if(_currentlyPlayingTitle.at(_currentlyPlayingTitle.size()-1) == ' ')
            _currentlyPlayingTitle.remove(_currentlyPlayingTitle.size()-1,_currentlyPlayingTitle.size()-1);
        if(_currentlyPlayingTitle.at(_currentlyPlayingTitle.size()-1) == '(')
            _currentlyPlayingTitle.remove(_currentlyPlayingTitle.size()-1,_currentlyPlayingTitle.size()-1);
    }while(_currentlyPlayingTitle.at(_currentlyPlayingTitle.size()-1) == ' ');
}

const QList<QMediaContent> * basePlayer::getMediaContentFromFilePaths(const QStringList *filenames)
{
    QList<QMediaContent> * media = new QList<QMediaContent>;

    for(QStringList::const_iterator i = filenames->begin(); i < filenames->end(); i++)
        media->push_back(QMediaContent(QUrl::fromLocalFile(*i)));

    return media;
}

QStringList * basePlayer::openFileDialog()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setMinimumSize(QSize(this->width(),this->height()));

    openFileDialog.setDirectory(QStandardPaths::locate(QStandardPaths::MusicLocation,"",QStandardPaths::LocateDirectory));
    openFileDialog.setNameFilter(getAudioFileTypes()->toStdString().c_str());
    openFileDialog.setViewMode(QFileDialog::List);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList * files = new QStringList();

    if(openFileDialog.exec())
       files->append(openFileDialog.selectedFiles());

    return files;
}

const QString * basePlayer::getAudioFileTypes()
{
    return new QString("Audio (*.mp3 *.mp4 *.wav *.flac *.ogg *.aiff *.wma *.mid *.ra *.ram "
                       "*.rm *.vox *.raw *.aac *.au *.ac3 *.m4a *.amr *.mod *.669 *.s3m *.mtm)");
}

void basePlayer::initiateAddMedia()
{
    addMedia(*getMediaContentFromFilePaths(openFileDialog()));
}

void basePlayer::initiateOpenMedia()
{
    openMedia(*getMediaContentFromFilePaths(openFileDialog()));
}
