#ifndef COMPONENTACTIONS_H
#define COMPONENTACTIONS_H
#include "mainwindow.h"

void MainWindow::play()
{
    _playButtonIsPressed();
}

void MainWindow::nextSong()
{
    _nextButtonIsPressed();
}

void MainWindow::previousSong()
{
    _prevButtonIsPressed();
}

void MainWindow::_playButtonIsPressed ()
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
    if(!_playlist->isEmpty())
    {
        _playlistView->item(_playlist->currentIndex())->setTextColor("black");
        _playlist->next();
        _playlistView->item(_playlist->currentIndex())->setTextColor("red");
    }
}

void MainWindow::_prevButtonIsPressed ()
{
    if(!_playlist->isEmpty())
    {
        _playlistView->item(_playlist->currentIndex())->setTextColor("black");
        _playlist->previous();
        _playlistView->item(_playlist->currentIndex())->setTextColor("red");
    }

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
            _playlistView->item(_playlist->currentIndex())->setTextColor("black");
            _playlist->setCurrentIndex(i);
            _playlistView->item(_playlist->currentIndex())->setTextColor("red");
            break;
        }
    }
}

#endif // COMPONENTACTIONS_H
