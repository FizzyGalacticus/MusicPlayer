#ifndef MENUACTIONS_H
#define MENUACTIONS_H
#include "mainwindow.h"

void MainWindow::open()
{
    QStringList fileNames = _openFileDialogue();

    if(fileNames.size())
    {
        QList<QMediaContent> playListFiles;

        for(QStringList::iterator file = fileNames.begin(); file < fileNames.end(); file++)
           playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

        _currentPlaylist->clear();
        _currentPlaylist->addMedia(playListFiles);
        _currentPlaylist->setCurrentIndex(0);
        _player->stop();
        _player->setPlaylist(_currentPlaylist);

        if(_isPlaying) _playButtonIsPressed();

        refreshPlaylistView();
    }
}

void MainWindow::addMedia()
{
    QStringList fileNames = _openFileDialogue();

    if(fileNames.size())
    {
        QList<QMediaContent> playListFiles;

        for(QStringList::iterator file = fileNames.begin(); file < fileNames.end(); file++)
           playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

        if(_currentPlaylist->isEmpty())
        {
            _currentPlaylist->addMedia(playListFiles);
            _currentPlaylist->setCurrentIndex(0);
            _player->setPlaylist(_currentPlaylist);
        }
        else _currentPlaylist->addMedia(playListFiles);

        refreshPlaylistView();
    }
}

void MainWindow::about()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("CS 372 - Software Construction"
               "<p>Final Project - \"Music Player\""
               "<p>Spring Semester 2014"));
}

void MainWindow::aboutQt()
{
    _infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::aboutAuthors()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about
            (
                this,
                tr("Authors Menu"),
                tr
                (
                    "<b><center>Authors:</center></b>"
                    "<p>Dustin Dodson"
                    "<p>Erik Talvi"
                    "<p>Matthew Parrish"
                    "<p>Nate Helms"
                    "<p>Nicholas Mardeusz"
                    "<p>Thomas Cerny"
                )
            );
}

#endif // MENUACTIONS_H
