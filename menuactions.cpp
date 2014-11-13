#ifndef MENUACTIONS_H
#define MENUACTIONS_H
#include "mainwindow.h"
#include <QAction>

void MainWindow::menuOpen()
{
    openMedia(_openFileDialog(getAudioFileTypes(),_defaultMusicDirectory));
}

void MainWindow::menuAddMedia()
{
    addMedia(_openFileDialog(getAudioFileTypes(),_defaultMusicDirectory));
}

void MainWindow::about()
{
#ifndef __ANDROID__
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
#endif
    QMessageBox::about(this, tr("About Menu"),
            tr("CS 372 - Software Construction"
               "<p>Final Project - \"<a href='https://github.com/FizzyGalacticus/MusicPlayer'>Music Player</a>\""
               "<p>Spring Semester 2014"
               "<p><b>Instructor:</b> Chris Hartman"));
}

void MainWindow::aboutQt()
{
#ifndef __ANDROID__
    _infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
#endif
}

void MainWindow::aboutAuthors()
{
#ifndef __ANDROID__
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
#endif
    QMessageBox::about
            (
                this,
                tr("Authors Menu"),
                tr
                (
                    "<b><center>Authors:</center></b>"
                    "<p>Dustin Dodson"

                    "<b><center>Previous Contributors:</center></b>"
                    "<p>Erik Talvi"
                    "<p>Matthew Parrish"
                    "<p>Nate Helms"
                    "<p>Nicholas Mardeusz"
                    "<p>Thomas Cerny"
                )
            );
}

void MainWindow::menuToggleLyricsBox()
{
    if(_lyricsTextBox->isHidden())
    {
        _lyricsTextBox->show();
        _toggleLyricsBox->setText(tr("Hide Lyrics"));
    }
    else
    {
        _lyricsTextBox->hide();
        _toggleLyricsBox->setText(tr("Show Lyrics"));
    }
}

#endif // MENUACTIONS_H
