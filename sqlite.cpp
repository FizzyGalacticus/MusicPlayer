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
    QDir * playlistDirectory = new QDir((*defaultMusicDirectory + "Playlist"));
    if(!playlistDirectory->exists()) playlistDirectory->mkdir(playlistDirectory->absolutePath());
    QStringList returnedFileNames = _openFileDialog(new QString("SQLite Database (*.db)"),new QString(playlistDirectory->absolutePath()));
    QString fileName = "";

    if(returnedFileNames.count()) fileName = returnedFileNames.at(0);

    if(QFile(fileName).exists())
    {
        qDebug() << "File already exists!";
        //FILE ALREADY EXISTS
    }
    else return writePlaylist(fileName);
}

bool MainWindow::writePlaylist(const QString & playlistName)
{
    QSqlDatabase * playlistDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",playlistName));

    bool ok = playlistDatabase->open();

    if(ok)
    {
        //Perform saving of plist here;

        playlistDatabase->close();
        return true;
    }
    else return false;
}
