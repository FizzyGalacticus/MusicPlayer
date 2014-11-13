#ifndef MENUS_H
#define MENUS_H
#include "mainwindow.h"
#include <QObject>
#include <QtWidgets>

void MainWindow::createMenus()
{
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_exitAct);

#ifndef __ANDROID__

    _playMenu = menuBar()->addMenu(tr("&Play"));
    _playMenu->addSeparator();
    _playMenu->addAction(_playAct);
    _playMenu->addAction(_nextSongAct);
    _playMenu->addAction(_previousSongAct);

    _optionsMenu = menuBar()->addMenu(tr("&Options"));
    _optionsMenu->addAction(_openAct);
    _optionsMenu->addAction(_addMediaAct);
    _optionsMenu->addSeparator();
    _optionsMenu->addAction(_savePlaylistAct);
    _optionsMenu->addAction(_loadPlaylistAct);
    _optionsMenu->addSeparator();
    _optionsMenu->addAction(_toggleLyricsBox);
#endif

    _helpMenu = menuBar()->addMenu(tr("&Help"));
    _helpMenu->addAction(_aboutAct);
    _helpMenu->addAction(_aboutQtAct);
    _helpMenu->addAction(_aboutAuthorsAct);
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
