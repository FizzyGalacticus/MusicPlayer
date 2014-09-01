#ifndef COMPONENTACTIONS_H
#define COMPONENTACTIONS_H
#include "mainwindow.h"
#include <QDebug>

void MainWindow::_prevButtonIsPressed ()
{
    if(!_currentPlaylist->isEmpty() && (_currentPlaylist->currentMedia() != _currentPlaylist->media(0) || _currentPlaylist->playbackMode() == QMediaPlaylist::Loop))
        _currentPlaylist->previous();
}

void MainWindow::_playButtonIsPressed()
{
    if(!_currentPlaylist->isEmpty())
    {
        if(!_isPlaying)
        {
            _playButton->setIcon(_playButtonPauseIcon);
            _playAct->setIcon(_playButtonPauseIcon);
            _player->play();
        }
        else
        {
            _playButton->setIcon(_playButtonPlayIcon);
            _playAct->setIcon(_playButtonPlayIcon);
            _player->pause();
        }

        _isPlaying = !_isPlaying;
    }
}

void MainWindow::_nextButtonIsPressed()
{
    if(!_currentPlaylist->isEmpty() && (_currentPlaylist->currentMedia() != _currentPlaylist->media(_currentPlaylist->mediaCount()-1) || _currentPlaylist->playbackMode() == QMediaPlaylist::Loop))
        _currentPlaylist->next();
}

void MainWindow::_newPlaylistTabButtonIsPressed()
{
    QListWidget * newPlaylistView = new QListWidget;

    _playlistViews->push_back(newPlaylistView);
    _playlistTabs->addTab(newPlaylistView,("Playlist " + QString::number(_playlistViews->count())));

    qDebug() << "Added new playlist tab!";
}

void MainWindow::_volumeSliderValueChanged()
{
        _player->setVolume(_volumeSlider->value());
}

void MainWindow::playbackPositionChanged(qint64 position)
{
    _progressBar->setValue(position);
}

void MainWindow::durationHasChanged(qint64 duration)
{
    QString labelStr = getAudioInfo();

    _fileMetadata->setText(labelStr);
    _progressBar->setRange(0,duration);

    for(int i = 0; i < _currentPlaylist->mediaCount(); i++)
    {
        if(i == _currentPlaylist->currentIndex())
            _currentPlaylistView->item(i)->setTextColor("red");
        else _currentPlaylistView->item(i)->setTextColor("black");
    }
}

void MainWindow::_shuffleButtonHasBeenPressed()
{
    _currentPlaylist->shuffle();
    refreshPlaylistView();
}

void MainWindow::playlistItemHasBeenClicked(QListWidgetItem * item)
{
    for(int i = 0; i < _currentPlaylist->mediaCount(); i++)
    {
        if(_currentPlaylist->media(i).canonicalUrl().fileName() == item->text())
        {
            _currentPlaylist->setCurrentIndex(i);
            resetPlaylistViewFunctionality(item);

            qDebug() << item->text() << "Double clicked!";
            break;
        }
    }
}

void MainWindow::resetPlaylistViewFunctionality(QListWidgetItem* item)
{
    _currentPlaylistView->setDisabled(true);
    _currentPlaylistView->setDisabled(false);

    if(item) qDebug() << "Reset _currentPlaylistView.";
}

void MainWindow::_loopCheckboxStateHasChanged(int state)
{
    if(state) _currentPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    else _currentPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::_tabCloseRequested(int index)
{
    qDebug() << index;
    if(_playlistTabs->count() == 1)
    {

    }
    else
    {
//        if(_currentPlaylist == _playlists->at(index))
//        {
//            if(index == _playlists->size()-1)
//                _currentPlaylist = _playlists->at(index-1);
//            else _currentPlaylist = _playlists->at(index+1);
//        }

//        if(_currentPlaylistView == _playlistViews->at(index))
//        {
//            if(index == _playlistViews->size()-1)
//                _currentPlaylistView = _playlistViews->at(index-1);
//            else _currentPlaylistView = _playlistViews->at(index+1);
//        }
//        qDebug() << "Moved things around!";
//        _playlistTabs->removeTab(index);
//        _playlistViews->remove(index);
//        _playlists->remove(index);
    }
}

#endif // COMPONENTACTIONS_H
