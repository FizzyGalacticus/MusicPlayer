#include <mainwindow.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

bool MainWindow::savePlaylist()
{
    QString * defaultMusicDirectory = new QString(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory));
    QDir * playlistDirectory = new QDir((*defaultMusicDirectory + "Playlists"));
    if(!playlistDirectory->exists()) playlistDirectory->mkdir(playlistDirectory->absolutePath());
    QStringList returnedFileNames = _openFileDialog(new QString("SQLite Database (*.db)"),new QString(playlistDirectory->absolutePath()));
    QFile * databaseFile = new QFile;

    if(returnedFileNames.count())
    {
        if(databaseFile->fileName().endsWith(".db")) databaseFile->setFileName(returnedFileNames.at(0));
        else databaseFile->setFileName(returnedFileNames.at(0) + ".db");
    }

    if(databaseFile->exists())
    {
        qDebug() << "File already exists!";
        //FILE ALREADY EXISTS
        return false;
    }
    else return writePlaylist(databaseFile);
}

bool MainWindow::writePlaylist(const QFile * playlistLocation)
{
    QSqlDatabase * playlistDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",playlistLocation->fileName()));
    playlistDatabase->setDatabaseName(playlistLocation->fileName());

    bool ok = playlistDatabase->open();

    if(ok)
    {
        QSqlQuery * dbquery = new QSqlQuery(*playlistDatabase);
        dbquery->exec("CREATE TABLE audiofiles(TITLE TEXT UNIQUE)");

        for(int i = 0; i < _playlistViews->at(_playlistTabs->currentIndex())->count(); i++)
        {
            QString query = (
                        "INSERT INTO audiofiles VALUES (\"" +
                        _playlistViews->at(_playlistTabs->currentIndex())->item(i)->text() +
                        "\")");
            dbquery->exec(query);
        }
        //Perform saving of plist here;

        playlistDatabase->close();
        return true;
    }
    else return false;
}
