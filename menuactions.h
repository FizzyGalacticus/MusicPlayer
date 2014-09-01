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

        _currentPlayer->playlist()->clear();
        _currentPlayer->playlist()->addMedia(playListFiles);
        _currentPlayer->playlist()->setCurrentIndex(0);
        _currentPlayer->stop();
        _currentPlayer->setPlaylist(_currentPlayer->playlist());

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

        if(_players->at(_playlistTabs->currentIndex())->playlist() && _players->at(_playlistTabs->currentIndex())->playlist()->isEmpty())
        {
            _players->at(_playlistTabs->currentIndex())->playlist()->addMedia(playListFiles);
            _players->at(_playlistTabs->currentIndex())->playlist()->setCurrentIndex(0);
        }
        else _players->at(_playlistTabs->currentIndex())->playlist()->addMedia(playListFiles);

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
