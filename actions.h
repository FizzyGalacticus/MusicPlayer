#ifndef ACTIONS_H
#define ACTIONS_H
#include "mainwindow.h"
#include <QtWidgets>

void MainWindow::createActions()
{
    _openAct = new QAction(tr("&Open..."), this);
    _openAct->setStatusTip(tr("Open existing files"));
    _openAct->setIcon(_openIcon);
    connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));

    _addMediaAct = new QAction(tr("&Add Media"), this);
    _addMediaAct->setStatusTip(tr("Add existing files to current playlist"));
    _addMediaAct->setIcon(_openIcon);
    connect(_addMediaAct, SIGNAL(triggered()), this, SLOT(addMedia()));

    _exitAct = new QAction(tr("&Exit"), this);
    _exitAct->setStatusTip(tr("Exit the application"));
    _exitAct->setIcon(_exitIcon);
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    _playAct = new QAction(tr("&Play/Pause"), this);
    _playAct->setStatusTip(tr("Play a song"));
    _playAct->setIcon(_playButtonPlayIcon);
    connect(_playAct, SIGNAL(triggered()), this, SLOT(_playButtonIsPressed()));

    _nextSongAct = new QAction(tr("&Next Song"), this);
    _nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    _nextSongAct->setIcon(_nextButtonIcon);
    connect(_nextSongAct, SIGNAL(triggered()), this, SLOT(_nextButtonIsPressed()));

    _previousSongAct = new QAction(tr("&Previous Song"), this);
    _previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
    _previousSongAct->setIcon(_prevButtonIcon);
    connect(_previousSongAct, SIGNAL(triggered()), this, SLOT(_prevButtonIsPressed()));

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

void MainWindow::refreshPlaylistView()
{
    _playlistView->clear();

    for(int i = 0; i < _playlist->mediaCount(); i++)
    {
        _playlistView->addItem(_playlist->media(i).canonicalUrl().fileName());
    }

    _playlistView->item(_playlist->currentIndex())->setTextColor("red");
    _playlistView->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ((event->key()==Qt::Key_O) && (event->modifiers()==Qt::CTRL))
            open();
    else if(event->key()==Qt::Key_P || event->key() == Qt::Key_MediaPlay || event->key() == Qt::Key_MediaPause)
        _playButtonIsPressed();
    else if(event->key() == Qt::Key_Period)
        _nextButtonIsPressed();
    else if(event->key() == Qt::Key_Comma)
        _prevButtonIsPressed();
    else if(event->key() == Qt::Key_A)
        addMedia();
    else if((event->key()==Qt::Key_Q) && (event->modifiers()==Qt::CTRL))
        close();
}

QStringList MainWindow::_openFileDialogue()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setNameFilter
            (
                tr
                (
                    "Audio (*.mp3 *.mp4 *.wav *.flac *.ogg *.aiff *.wma *.mid *.ra *.ram *.rm *.vox *.raw *.aac *.au *.ac3 *.m4a *.amr *.mod *.669 *.s3m *.mtm)"
                )
            );
    openFileDialog.setViewMode(QFileDialog::List);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList fileNames;

    if(openFileDialog.exec())
       fileNames = openFileDialog.selectedFiles();

    return fileNames;
}

#endif // ACTIONS_H
