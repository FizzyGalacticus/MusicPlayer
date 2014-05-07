#ifndef ACTIONS_H
#define ACTIONS_H
#include "mainwindow.h"
#include <QtWidgets>

void MainWindow::createActions()
{
    _openAct = new QAction(tr("&Open..."), this);
    _openAct->setStatusTip(tr("Open an existing file"));
    _openAct->setIcon(_openIcon);
    connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));

    _exitAct = new QAction(tr("&Exit"), this);
    _exitAct->setStatusTip(tr("Exit the application"));
    _exitAct->setIcon(_exitIcon);
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    _playAct = new QAction(tr("&Play/Pause"), this);
    _playAct->setStatusTip(tr("Play a song"));
    _playAct->setIcon(_playButtonPlayIcon);
    connect(_playAct, SIGNAL(triggered()), this, SLOT(play()));

    _nextSongAct = new QAction(tr("&Next Song"), this);
    _nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    _nextSongAct->setIcon(_nextButtonIcon);
    connect(_nextSongAct, SIGNAL(triggered()), this, SLOT(nextSong()));

    _previousSongAct = new QAction(tr("&Previous Song"), this);
    _previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
    _previousSongAct->setIcon(_prevButtonIcon);
    connect(_previousSongAct, SIGNAL(triggered()), this, SLOT(previousSong()));

    _aboutAct = new QAction(tr("&About"), this);
    _aboutAct->setStatusTip(tr("Show the application's About box"));
    _aboutAct->setIcon(_helpIcon);
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

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

void MainWindow::addItemsToPlaylistView()
{
    _playlistView->clear();

    for(int i = 0; i < _playlist->mediaCount(); i++)
    {
        _playlistView->addItem(_playlist->media(i).canonicalUrl().fileName());
    }

    _playlistView->show();
}

#endif // ACTIONS_H
