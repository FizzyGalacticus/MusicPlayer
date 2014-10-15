#include <mainwindow.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>


bool MainWindow::savePlaylist()
{
    QString temp = "";

    for(int i = 0; i < QString("Playlist").count(); i++)
        temp += _playlistTabs->tabText(_playlistTabs->currentIndex()).at(i);

    if(temp != "Playlist"); //Playlist already exists!

    return true;
}
