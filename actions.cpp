#ifndef ACTIONS_H
#define ACTIONS_H
#include <mainwindow.h>
#include <QtWidgets>
#include <QStandardPaths>
#include <QStringList>
#include <QDebug>
#include <QThread>

void MainWindow::createActions()
{
    _openAct = new QAction(tr("&Open..."), this);
    _openAct->setStatusTip(tr("Open existing files"));
    _openAct->setIcon(_openIcon);
    connect(_openAct, SIGNAL(triggered()), this, SLOT(menuOpen()));

    _addMediaAct = new QAction(tr("&Add Media"), this);
    _addMediaAct->setStatusTip(tr("Add existing files to current playlist"));
    _addMediaAct->setIcon(_openIcon);
    connect(_addMediaAct, SIGNAL(triggered()), this, SLOT(menuAddMedia()));

    _exitAct = new QAction(tr("&Exit"), this);
    _exitAct->setStatusTip(tr("Exit the application"));
    _exitAct->setIcon(_exitIcon);
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    _playAct = new QAction(tr("&Play/Pause"), this);
    _playAct->setStatusTip(tr("Play a song"));
    _playAct->setIcon(_playButtonPlayIcon);
    connect(_playAct, SIGNAL(triggered()), this, SLOT(_playButtonIsPressed()));

    _nextSongAct = new QAction(tr("&Next Song"), this);
    _nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    _nextSongAct->setIcon(_nextButtonIcon);
    connect(_nextSongAct, SIGNAL(triggered()), this, SLOT(_nextButtonIsPressed()));

    _previousSongAct = new QAction(tr("&Previous Song"), this);
    _previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
    _previousSongAct->setIcon(_prevButtonIcon);
    connect(_previousSongAct, SIGNAL(triggered()), this, SLOT(_prevButtonIsPressed()));

    _aboutAct = new QAction(tr("&About"), this);
    _aboutAct->setStatusTip(tr("Show the application's About box"));
    _aboutAct->setIcon(_helpIcon);
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    _savePlaylistAct = new QAction(tr("&Save Playlist"),this);
    connect(_savePlaylistAct, SIGNAL(triggered()), this, SLOT(savePlaylist()));
    _loadPlaylistAct = new QAction(tr("&Load Playlist"), this);
    connect(_loadPlaylistAct, SIGNAL(triggered()), this, SLOT(loadPlaylist()));

    _aboutQtAct = new QAction(tr("About &Qt"), this);
    _aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    _aboutQtAct->setIcon(_qtIcon);
    connect(_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(_aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    _aboutAuthorsAct = new QAction(tr("About &Authors"), this);
    _aboutAuthorsAct->setStatusTip(tr("Show information about Music Player's authors"));
    _aboutAuthorsAct->setIcon(_infoIcon);
    connect(_aboutAuthorsAct, SIGNAL(triggered()),this, SLOT(aboutAuthors()));
}

void MainWindow::refreshPlaylistView()
{
    _playlistViews->at(_playlistTabs->currentIndex())->clear();

    for(int i = 0; i < _players->at(_playlistTabs->currentIndex())->playlist()->mediaCount(); i++)
    {
        _playlistViews->at(_playlistTabs->currentIndex())->addItem(_players->at(_playlistTabs->currentIndex())->playlist()->media(i).canonicalUrl().fileName());
    }

    if(_players->at(_playlistTabs->currentIndex())->playlist()->mediaCount())
        _playlistViews->at(_playlistTabs->currentIndex())->item(_players->at(_playlistTabs->currentIndex())->playlist()->currentIndex())->setTextColor("red");
    _playlistViews->at(_playlistTabs->currentIndex())->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ((event->key()==Qt::Key_O) && (event->modifiers() == Qt::CTRL))
        menuOpen();
    else if(event->key()==Qt::Key_P || event->key() == Qt::Key_MediaPlay || event->key() == Qt::Key_MediaPause)
        _playButtonIsPressed();
    else if(event->key() == Qt::Key_MediaNext)
        _nextButtonIsPressed();
    else if(event->key() == Qt::Key_MediaPrevious)
        _prevButtonIsPressed();
    else if(event->key() == Qt::Key_A && (event->modifiers() == Qt::CTRL))
        menuAddMedia();
    else if(event->key() == Qt::Key_S && (event->modifiers() == Qt::CTRL))
        qDebug() << savePlaylist(_playlistTabs->currentIndex());
    else if(event->key() == Qt::Key_L && (event->modifiers() == Qt::CTRL))
        qDebug() << loadPlaylist(_playlistTabs->currentIndex());
    else if((event->key()==Qt::Key_Q) && (event->modifiers()==Qt::CTRL))
        close();
}

const QString * MainWindow::getAudioFileTypes()
{
    return new QString("Audio (*.mp3 *.mp4 *.wav *.flac *.ogg *.aiff *.wma *.mid *.ra *.ram "
                       "*.rm *.vox *.raw *.aac *.au *.ac3 *.m4a *.amr *.mod *.669 *.s3m *.mtm)");
}

void MainWindow::addMedia(const QStringList * media)
{
    if(media->size())
    {
        QList<QMediaContent> playListFiles;

        for(QStringList::const_iterator file = media->begin(); file < media->end(); file++)
            playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

        if(_players->at(_playlistTabs->currentIndex())->playlist())
        {
            if(_players->at(_playlistTabs->currentIndex())->playlist()->isEmpty())
            {
                _players->at(_playlistTabs->currentIndex())->playlist()->addMedia(playListFiles);
                _players->at(_playlistTabs->currentIndex())->playlist()->setCurrentIndex(0);
            }
            else _players->at(_playlistTabs->currentIndex())->playlist()->addMedia(playListFiles);
        }

        refreshPlaylistView();
    }
}

void MainWindow::openMedia(const QStringList * media)
{
    if(media->size())
    {
        QList<QMediaContent> playListFiles;

        for(QStringList::const_iterator file = media->begin(); file < media->end(); file++)
           playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

        if(_currentPlayer == _players->at(_playlistTabs->currentIndex()))
        {
            _currentPlayer->pause();
            _currentPlayer->playlist()->clear();
            _currentPlayer->playlist()->addMedia(playListFiles);
            _currentPlayer->playlist()->setCurrentIndex(0);

            if(_isPlaying) _currentPlayer->play();
        }
        else
        {
            _players->at(_playlistTabs->currentIndex())->playlist()->clear();
            _players->at(_playlistTabs->currentIndex())->playlist()->addMedia(playListFiles);
            _players->at(_playlistTabs->currentIndex())->playlist()->setCurrentIndex(0);
        }

        refreshPlaylistView();
    }
}

QStringList * MainWindow::_openFileDialog(const QString * fileTypes, const QString * startingLocation)
{
    QFileDialog openFileDialog(this);
    openFileDialog.setMinimumSize(QSize(this->width(),this->height()));

    openFileDialog.setDirectory(*startingLocation);
    openFileDialog.setNameFilter(tr(fileTypes->toStdString().c_str()));
    openFileDialog.setViewMode(QFileDialog::List);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList * files = new QStringList();

    if(openFileDialog.exec())
       files->append(openFileDialog.selectedFiles());

    return files;
}

const QString MainWindow::getAudioInfo(const int & index)
{
    QString metaData = "";

    if(_players->at(index)->availableMetaData().contains("Title"))
    {
        QString songTitle = _players->at(index)->metaData("Title").toString();
        if(_players->at(index)->availableMetaData().contains("AlbumArtist"))
        {
            QString songArtist = _players->at(index)->metaData("AlbumArtist").toString();
            metaData =(songArtist + " - " + songTitle);
            updateSongLyrics(songArtist,songTitle);
        }
        else metaData = songTitle;
    }
    else
    {
        _lyricsTextBox->setText("");
        return _players->at(index)->currentMedia().canonicalUrl().fileName();
    }

    return metaData;
}

#endif // ACTIONS_H
