#include "mediadatabase.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <QFile>

mediaDatabase::mediaDatabase(QObject *parent) :
    QObject(parent),
    _db(QSqlDatabase::addDatabase("QMYSQL","Media-Player")),
    _query(new QSqlQuery(_db))
{
    _db.setHostName("127.0.0.1");
    _db.setUserName("root");
    _db.setPassword("rootpass");

    initiateSchema();
}

mediaDatabase::~mediaDatabase()
{

}

bool mediaDatabase::addArtist(const QString & newArtist)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        if(!_query->exec("USE Media_Player;"))
            qDebug() << "Could not open `Media_Player` schema.";
        if(!checkIfValueExists("Artist","name",newArtist))
        {
            if(!_query->exec("INSERT INTO `Media_Player`.`Artist` (name) VALUES ('" + newArtist + "');"))
                qDebug() << _query->lastError().text();
            else succeeded = true;
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to add new artist.";
    }

    return succeeded;
}

bool mediaDatabase::addAlbum(const QString &albumArtist, const QString &newAlbum)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString artist = insertFormattingCharacters(albumArtist),
                album = insertFormattingCharacters(newAlbum);

        QString qry = "INSERT INTO `Media_Player`.`Album` "
                "(Title, Artist_name) VALUES (':album', ':artist');";
        qry.replace(":album", album);
        qry.replace(":artist", artist);

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else succeeded = true;

        _db.close();
    }
    else
    {
        qDebug() << "Could not open datase to add album:" << newAlbum;
    }

    return succeeded;
}

bool mediaDatabase::addSong(const QString &songTitle, const QString &albumTitle, const QString &artistName)
{
    QString song = insertFormattingCharacters(songTitle), album = insertFormattingCharacters(albumTitle),
            artist = insertFormattingCharacters(artistName);

    if(artist == "" || album == "" || song == "")
        return false;

    addArtist(artist);
    addAlbum(artist,album);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "INSERT INTO `Media_Player`.`Song` "
                      "(Title, Album_Title, Album_Artist_name) "
                      "VALUES (':song', ':album', ':artist');";
        qry.replace(":song", song);
        qry.replace(":album", album);
        qry.replace(":artist", artist);

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else succeeded = true;
    }
    else
    {
        qDebug() << "Could not open database to insert new song:" << song;
    }

    return succeeded;
}

bool mediaDatabase::addLyrics(const QString &artistName, const QString &songTitle, const QString & newLyrics)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString lyrics = insertFormattingCharacters(newLyrics),
                artist = insertFormattingCharacters(artistName),
                title = insertFormattingCharacters(songTitle),
                qry = "UPDATE `Media_Player`.`Song` "
                "SET lyrics=':lyrics' "
                "WHERE Album_Artist_name=':artist' AND "
                "Title=':song';";
        qry.replace(":artist",artist).replace(":song",title).replace(":lyrics", lyrics);

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else succeeded = true;

        _db.close();
    }
    else qDebug() << "Could not open database to add lyrics for song:" << songTitle;

    return succeeded;
}

bool mediaDatabase::incrementSongCounter(const QString &songTitle, const QString &albumTitle, const QString &artistName)
{
    const QString artist = insertFormattingCharacters(artistName), album = insertFormattingCharacters(albumTitle),
            song = insertFormattingCharacters(songTitle);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "UPDATE `Media_Player`.`Song` "
                "SET `numberOfListens` = `numberOfListens` + 1 "
                "WHERE `Album_Artist_name` = ':artist' "
                "AND `Album_Title` = ':album' "
                "AND `Title` = ':song';";
        qry.replace(":artist", artist);
        qry.replace(":album", album);
        qry.replace(":song", song);

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else    succeeded = true;

        _db.close();
    }
    else qDebug() << "Could not open database to increment listens for song:" << song;

    return succeeded;
}

void mediaDatabase::initiateSchema()
{
    bool ok = _db.open();

    if(ok)
    {
        qDebug() << "Database opened!";
        bool schemaExists = false;

        if(!_query->exec("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = 'Media_Player';"))
            qDebug() << _query->lastError().text();
        else
        {
            while(_query->next())
                schemaExists = _query->value(0).toBool();

            if(!schemaExists)
            {
                QFile::copy(":/resources/schema.sql","schema.sql");
                QFile * schemaFile = new QFile("schema.sql");
                schemaFile->open(QFile::ReadOnly);
                if(!_query->exec(QString(schemaFile->readAll())))
                    qDebug() << _query->lastError().text();
                else qDebug() << "Created schema.";
                schemaFile->close();

                schemaFile->remove();
            }
            else qDebug() << "Schema exists!";
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database!";
        qDebug() << "Error:" << _db.lastError().text();
    }
}

bool mediaDatabase::checkIfValueExists(const QString & tableName, const QString & columnName, const QString & value)
{
    bool exists = true;

    if(!_query->exec("SELECT COUNT(*) FROM `Media_Player`.`" + tableName + "` WHERE `" + columnName + "`='" + value + "';"))
        qDebug() << "Could not check the existence of" << value;
    else
    {
        _query->next();
        if(!_query->value(0).toBool()) exists = false;
    }

    return exists;
}

const QString mediaDatabase::insertFormattingCharacters(const QString &str) const
{
    QString newStr = str;
    newStr.replace("'","\\'");
    newStr.replace("\"","\\\"");
    newStr.replace("\n", "\\n");

    return newStr;
}

int mediaDatabase::getId(const QString &tableName, const QString &columnValue)
{
    bool ok = _db.open();
    int id = -1;

    if(ok)
    {
        QString columnTitle = "";

        if(tableName == "Song" || tableName == "Album")
            columnTitle = "Title";
        else if(tableName == "Artist")
            columnTitle = "name";

        if(!_query->exec("SELECT `id` FROM `Media_Player`.`" + tableName + "` WHERE `" + columnTitle + "`='" + columnValue + "';"))
        {
            qDebug() << "Could not execute:" << _query->lastQuery();
        }
        else
        {
            _query->next();
            id = _query->value(0).toInt();
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to get id for table" << tableName;
    }

    return id;
}
