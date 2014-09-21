#ifndef COMPONENTACTIONS_H
#define COMPONENTACTIONS_H
#include "mainwindow.h"
#include <QDebug>

void MainWindow::_prevButtonIsPressed ()
{
    if(!_currentPlayer->playlist()->isEmpty() && (_currentPlayer->playlist()->currentMedia() != _currentPlayer->playlist()->media(0) || _currentPlayer->playlist()->playbackMode() == QMediaPlaylist::Loop))
        _currentPlayer->playlist()->previous();
}

void MainWindow::_playButtonIsPressed()
{
    if(!_players->at(_playlistTabs->currentIndex())->playlist()->isEmpty())
    {
        if(_currentPlayer == _players->at(_playlistTabs->currentIndex()))
        {
            if(_isPlaying)
            {
                _currentPlayer->pause();
                _playButton->setIcon(_playButtonPlayIcon);
                _playAct->setIcon(_playButtonPlayIcon);

                _isPlaying = false;
            }
            else
            {
                _currentPlayer->play();
                _playButton->setIcon(_playButtonPauseIcon);
                _playAct->setIcon(_playButtonPauseIcon);

                _isPlaying = true;
            }
        }
        else
        {
            if(_isPlaying)
            {
                _currentPlayer->pause();
                _currentPlayer = _players->at(_playlistTabs->currentIndex());
                _playButton->setIcon(_playButtonPauseIcon);
                _playAct->setIcon(_playButtonPauseIcon);
                durationHasChanged(_currentPlayer->duration());
                _currentPlayer->play();

                _isPlaying = true;
            }
            else
            {
                _currentPlayer = _players->at(_playlistTabs->currentIndex());
                _playButton->setIcon(_playButtonPauseIcon);
                _playAct->setIcon(_playButtonPauseIcon);
                durationHasChanged(_currentPlayer->duration());
                _currentPlayer->play();

                _isPlaying = true;
            }

            _currentPlayer->setVolume(_volumeSlider->value());
        }
    }
}

void MainWindow::_nextButtonIsPressed()
{
    if(!_currentPlayer->playlist()->isEmpty() && (_currentPlayer->playlist()->currentMedia() != _currentPlayer->playlist()->media(_currentPlayer->playlist()->mediaCount()-1) || _currentPlayer->playlist()->playbackMode() == QMediaPlaylist::Loop))
        _currentPlayer->playlist()->next();
}

void MainWindow::_newPlaylistTabButtonIsPressed()
{
    QListWidget * newPlaylistView = new QListWidget;

    setupPlaylistViewConnections(newPlaylistView);

    _playlistViews->push_back(newPlaylistView);
    _playlistTabs->addTab(newPlaylistView,("Playlist " + QString::number(_playlistViews->count())));
    _players->push_back(new QMediaPlayer);
    _players->at(_players->count()-1)->setPlaylist(new QMediaPlaylist);
    _players->at(_players->count()-1)->playlist()->setCurrentIndex(0);

    connect(_players->at(_players->count()-1),SIGNAL(durationChanged(qint64)),this,SLOT(durationHasChanged(qint64)));
    connect(_players->at(_players->count()-1),SIGNAL(positionChanged(qint64)),this,SLOT(playbackPositionChanged(qint64)));

    qDebug() << "Added new playlist tab!";
}

void MainWindow::_volumeSliderValueChanged()
{
        _currentPlayer->setVolume(_volumeSlider->value());
}

void MainWindow::playbackPositionChanged(qint64 position)
{
    _progressBar->setValue(position);
}

void MainWindow::durationHasChanged(qint64 duration)
{
    int playerWhoseDurationChanged = -1;

    for(int player = 0; player < _players->count(); player++)
        if(_players->at(player)->duration() == duration)
        {
            playerWhoseDurationChanged = player;
            break;
        }

    if(playerWhoseDurationChanged != -1 && _currentPlayer == _players->at(playerWhoseDurationChanged))
    {
        QString labelStr = getAudioInfo(playerWhoseDurationChanged);

        _fileMetadata->setText(labelStr);
        _progressBar->setRange(0,duration);
    }

    if(playerWhoseDurationChanged != -1)
        for(int i = 0; i < _players->at(playerWhoseDurationChanged)->playlist()->mediaCount(); i++)
        {
            if(i == _players->at(playerWhoseDurationChanged)->playlist()->currentIndex())
                _playlistViews->at(playerWhoseDurationChanged)->item(i)->setTextColor("red");

            else _playlistViews->at(playerWhoseDurationChanged)->item(i)->setTextColor("black");
        }
}

void MainWindow::_shuffleButtonHasBeenPressed()
{
    _players->at(_playlistTabs->currentIndex())->playlist()->shuffle();
    refreshPlaylistView();
}

void MainWindow::playlistItemHasBeenClicked(QListWidgetItem * item)
{
    for(int i = 0; i < _players->at(_playlistTabs->currentIndex())->playlist()->mediaCount(); i++)
    {
        if(_players->at(_playlistTabs->currentIndex())->playlist()->media(i).canonicalUrl().fileName() == item->text())
        {
            _players->at(_playlistTabs->currentIndex())->playlist()->setCurrentIndex(i);
            resetPlaylistViewFunctionality(item);

            qDebug() << item->text() << "Double clicked!";
            break;
        }
    }
}

void MainWindow::resetPlaylistViewFunctionality(QListWidgetItem* item)
{
    //BROKEN
    _playlistViews->at(_playlistTabs->currentIndex())->setDisabled(true);
    _playlistViews->at(_playlistTabs->currentIndex())->setDisabled(false);

    if(item){}
}

void MainWindow::_loopCheckboxStateHasChanged(int state)
{
    if(state)
        for(int i = 0; i < _players->size(); i++)
            _players->at(i)->playlist()->setPlaybackMode(QMediaPlaylist::Loop);
    else
        for(int i = 0; i < _players->size(); i++)
            _players->at(i)->playlist()->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::_tabCloseRequested(int index)
{
    //If there is only one playlist/tab open
    if(_playlistTabs->count() == 1)
    {

    }
    else
    {
        qDebug() << "More than one tab!";
        if(_currentPlayer == _players->at(index))
            _currentPlayer->pause();
        if(_playlistTabs->currentIndex() == index)
        {
            qDebug() << "Trying to close the current tab!";
            if(index == (_playlistTabs->count()-1))
            {
                _playlistTabs->setCurrentIndex(index-1);
                _currentPlaylistView = _playlistViews->at(index-1);
                _currentPlayer = _players->at(index-1);
            }
            else
            {
                _playlistTabs->setCurrentIndex(index+1);
                _currentPlaylistView = _playlistViews->at(index+1);
                _currentPlayer = _players->at(index+1);
            }
        }

        _players->remove(index);
        _playlistTabs->removeTab(index);
        _playlistViews->remove(index);
    }
}

void MainWindow::_currentTabIndexHasChanged(int index)
{
    _currentPlaylistView = _playlistViews->at(index);

    if(_currentPlayer != _players->at(index))
    {
        _playButton->setIcon(_playButtonPlayIcon);
        _playAct->setIcon(_playButtonPlayIcon);
    }
    else
    {
        _playButton->setIcon(_playButtonPauseIcon);
        _playAct->setIcon(_playButtonPauseIcon);
    }
}

#endif // COMPONENTACTIONS_H
