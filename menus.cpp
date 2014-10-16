#ifndef MENUS_H
#define MENUS_H
#include "mainwindow.h"
#include <QObject>
#include <QtWidgets>

void MainWindow::createMenus()
{
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_exitAct);

    _helpMenu = menuBar()->addMenu(tr("&Help"));
    _helpMenu->addAction(_aboutAct);
    _helpMenu->addAction(_aboutQtAct);
    _helpMenu->addAction(_aboutAuthorsAct);

#ifndef __ANDROID__
    _fileMenu->addAction(_openAct);
    _fileMenu->addSeparator();
    _fileMenu->addAction(_addMediaAct);
    _fileMenu->addSeparator();

    _playMenu = menuBar()->addMenu(tr("&Play"));
    _playMenu->addSeparator();
    _playMenu->addAction(_playAct);
    _playMenu->addAction(_nextSongAct);
    _playMenu->addAction(_previousSongAct);

    _playlistMenu = menuBar()->addMenu(tr("&Playlist"));
    _playlistMenu->addAction(_savePlaylistAct);
    _playlistMenu->addAction(_loadPlaylistAct);
#endif
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(_playAct);
    menu.addAction(_nextSongAct);
    menu.addAction(_previousSongAct);
    menu.addAction(_addMediaAct);
    menu.exec(event->globalPos());
}

#endif // MENUS_H
