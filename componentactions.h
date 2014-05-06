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
    _playlist->next();
}

void MainWindow::_prevButtonIsPressed ()
{
    _playlist->previous();
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

void MainWindow::shuffleCheckboxHasChanged(int state)
{
    if(state) _playlist->shuffle();
}

#endif // COMPONENTACTIONS_H
