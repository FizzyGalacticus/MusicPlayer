#ifndef COMPONENTACTIONS_H
#define COMPONENTACTIONS_H
#include "mainwindow.h"

void MainWindow::_prevButtonIsPressed ()
{
    if(!_playlist->isEmpty() && (_playlist->currentMedia() != _playlist->media(0) || _playlist->playbackMode() == QMediaPlaylist::Loop))
        _playlist->previous();
}

void MainWindow::_playButtonIsPressed()
{
    if(!_playlist->isEmpty())
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
    if(!_playlist->isEmpty() && (_playlist->currentMedia() != _playlist->media(_playlist->mediaCount()-1) || _playlist->playbackMode() == QMediaPlaylist::Loop))
        _playlist->next();
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
    QString labelStr;

    if(_player->availableMetaData().contains("Title"))
    {
        QString songTitle = _player->metaData("Title").toString();
        if(_player->availableMetaData().contains("AlbumArtist"))
            labelStr =
                    (
                        _player->metaData("AlbumArtist").toString() + " - " +
                        songTitle
                    );
        else labelStr = songTitle;
    }
    else labelStr = _player->currentMedia().canonicalUrl().fileName();

    _fileMetadata->setText(labelStr);
    _progressBar->setRange(0,duration);

    for(int i = 0; i < _playlist->mediaCount(); i++)
    {
        if(i == _playlist->currentIndex()) _playlistView->item(i)->setTextColor("red");
        else _playlistView->item(i)->setTextColor("black");
    }
}

void MainWindow::_shuffleButtonHasBeenPressed()
{
    _playlist->shuffle();
    refreshPlaylistView();
}

void MainWindow::playlistItemHasBeenClicked(QListWidgetItem * item)
{
    for(int i = 0; i < _playlist->mediaCount(); i++)
    {
        if(_playlist->media(i).canonicalUrl().fileName() == item->text())
        {
            _playlist->setCurrentIndex(i);
            resetPlaylistViewFunctionality(item);
            break;
        }
    }
}

void MainWindow::resetPlaylistViewFunctionality(QListWidgetItem* item)
{
    _playlistView->setDisabled(true);
    _playlistView->setDisabled(false);
}

void MainWindow::_loopCheckboxStateHasChanged(int state)
{
    if(state) _playlist->setPlaybackMode(QMediaPlaylist::Loop);
    else _playlist->setPlaybackMode(QMediaPlaylist::Sequential);
}

#endif // COMPONENTACTIONS_H
