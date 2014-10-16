#include <mainwindow.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

bool MainWindow::savePlaylist(const int & index)
{
    QString * defaultMusicDirectory = new QString(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory));
    QDir * playlistDirectory = new QDir((*defaultMusicDirectory + "Playlists"));
    if(!playlistDirectory->exists()) playlistDirectory->mkdir(playlistDirectory->absolutePath());
    QStringList returnedFileNames = _openFileDialog(new QString("SQLite Database (*.db)"),new QString(playlistDirectory->absolutePath()));
    QFile * databaseFile = new QFile;

    if(returnedFileNames.count())
    {
        if(returnedFileNames.at(0).endsWith(".db")) databaseFile->setFileName(returnedFileNames.at(0));
        else databaseFile->setFileName(returnedFileNames.at(0) + ".db");
    }
    else return false;

    if(databaseFile->exists())
    {
        qDebug() << "File already exists!";
        //FILE ALREADY EXISTS
        return false;
    }
    else return writePlaylist(databaseFile, index);
}

bool MainWindow::writePlaylist(const QFile * playlistLocation, const int & index)
{
    QSqlDatabase * playlistDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",playlistLocation->fileName()));
    playlistDatabase->setDatabaseName(playlistLocation->fileName());

    bool ok = playlistDatabase->open();

    if(ok)
    {
        QSqlQuery * dbquery = new QSqlQuery(*playlistDatabase);
        dbquery->exec("CREATE TABLE audiofiles(TITLE TEXT UNIQUE)");

        for(int i = 0; i < _playlistViews->at(index)->count(); i++)
        {
            QString audioFilePath = _players->at(index)->playlist()->media(i).canonicalUrl().url();
            if(audioFilePath.contains("file:"))
                audioFilePath.remove(0,7);

            QString query = (
                        "INSERT INTO audiofiles VALUES (\"" +
                        audioFilePath +
                        "\")");
            dbquery->exec(query);
        }

        playlistDatabase->close();
        return true;
    }
    else return false;
}

const QStringList * MainWindow::readPlaylist(const QFile * playlistLocation)
{
    QStringList * playlistFiles = new QStringList;

    QSqlDatabase * playlistDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",playlistLocation->fileName()));
    playlistDatabase->setDatabaseName(playlistLocation->fileName());

    bool ok = playlistDatabase->open();

    if(ok)
    {
        QSqlQuery * dbquery = new QSqlQuery(*playlistDatabase);

        QString query = "SELECT * FROM audiofiles";
        dbquery->exec(query);

        while(dbquery->next()) playlistFiles->push_back(dbquery->value(0).toString());

        playlistDatabase->close();
    }

    return playlistFiles;
}

bool MainWindow::loadPlaylist(const int & index)
{
    if(_playlistViews->at(index)->count())
    {
        //There's already stuff in the playlist!
        return false;
    }

    QString * defaultMusicDirectory = new QString(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory));
    QDir * playlistDirectory = new QDir((*defaultMusicDirectory + "Playlists"));
    if(!playlistDirectory->exists()) playlistDirectory->mkdir(playlistDirectory->absolutePath());
    QStringList returnedFileNames = _openFileDialog(new QString("SQLite Database (*.db)"),new QString(playlistDirectory->absolutePath()));
    QFile * databaseFile = new QFile;

    if(returnedFileNames.count())
        databaseFile->setFileName(returnedFileNames.at(0));
    else return false;

    const QStringList * playlistFiles = readPlaylist(databaseFile);

    QList<QMediaContent> playlistMediaFiles;

    for(QStringList::const_iterator file = playlistFiles->constBegin(); file < playlistFiles->constEnd(); file++)
        playlistMediaFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

    _players->at(index)->stop();
    _players->at(index)->playlist()->clear();
    _players->at(index)->playlist()->addMedia(playlistMediaFiles);
    _players->at(index)->playlist()->setCurrentIndex(0);

    refreshPlaylistView();

    return true;
}
