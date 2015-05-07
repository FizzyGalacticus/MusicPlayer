#include "mediadatabase.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <QFile>
#include <QVector>

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
        const QString artist = insertFormattingCharacters(newArtist);

        if(!_query->exec("USE Media_Player;"))
            qDebug() << "Could not open `Media_Player` schema.";
        if(!checkIfValueExists("Artist","name",artist))
        {
            if(!_query->exec("INSERT INTO `Media_Player`.`Artist` (name) VALUES ('" + artist + "');"))
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

bool mediaDatabase::addAlbum(const int & artistId, const QString &newAlbum)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString album = insertFormattingCharacters(newAlbum);

        QString qry = "INSERT INTO `Media_Player`.`Album` "
                "(Title, Artist_id) VALUES (':album', ':artist');";
        qry.replace(":album", album);
        qry.replace(":artist", QString::number(artistId));

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
    if(artistName == "" || albumTitle == "" || songTitle == "")
        return false;

    addArtist(artistName);

    const int artistId = getArtistId(artistName);

    addAlbum(artistId,albumTitle);

    const int albumId = getAlbumId(artistName,albumTitle);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString song = insertFormattingCharacters(songTitle);

        QString qry = "INSERT INTO `Media_Player`.`Song` "
                      "(Title, Album_id) "
                      "VALUES (':song', ':album');";
        qry.replace(":song", song);
        qry.replace(":album", QString::number(albumId));

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else succeeded = true;
    }
    else
    {
        qDebug() << "Could not open database to insert new song.";
    }

    return succeeded;
}

bool mediaDatabase::addLyrics(const QString & artistName, const QString & songTitle, const QString & newLyrics)
{
    QString lyrics = insertFormattingCharacters(newLyrics),
            title = insertFormattingCharacters(songTitle);

    const int albumId = 3;//getAlbumId(artistName,albumTitle);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "UPDATE `Media_Player`.`Song` "
                "SET lyrics=':lyrics' "
                "WHERE Album_id=':album' AND "
                "Title=':song';";
        qry.replace(":album",QString::number(albumId)).replace(":song",title).replace(":lyrics", lyrics);

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

    const int & albumId = getAlbumId(artistName,albumTitle);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "UPDATE `Media_Player`.`Song` "
                "SET `numberOfListens` = `numberOfListens` + 1 "
                "WHERE `Album_id` = ':album' "
                "AND `Title` = ':song';";
        qry.replace(":album", QString::number(albumId));
        qry.replace(":song", song);

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else    succeeded = true;

        _db.close();
    }
    else qDebug() << "Could not open database to increment listens for song:" << song;

    return succeeded;
}

const QVector<QString> * mediaDatabase::login(const QString &username, const QString &password)
{
    bool ok = _db.open();
    QVector<QString> * results = new QVector<QString>;

    if(ok)
    {
        QString qry = "SELECT `fname`, `lname`, `email` "
                      "FROM `Media_Player`.`User` "
                      "WHERE `username`='" + username + "'"
                      "AND `password`='" + password + "';";

        if(!_query->exec(qry))
        {
            qDebug() << "Couldn't query for user:" << _query->lastError().text();
        }
        else
        {
            while(_query->next())
            {
                for(auto i = 0; i < 3; i++)
                    results->push_back(_query->value(i).toString());
            }
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to authenticate user.";
    }

    return results;
}

bool mediaDatabase::userExists(const QString &username)
{
    bool ok = _db.open(), exists = false;

    if(ok)
    {
        QString qry = "SELECT COUNT(*) FROM `Media_Player`.`User` "
                      "WHERE `username`='" + insertFormattingCharacters(username) + "';";

        if(!_query->exec(qry))
        {
            qDebug() << _query->lastError().text();
        }
        else
        {
            while(_query->next())
                exists = _query->value(0).toBool();
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to check if user exists.";
    }

    return exists;
}

bool mediaDatabase::createUser(const QString &username, const QString &password, const QString &fname, const QString &lname, const QString &email)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "INSERT INTO `Media_Player`.`User` "
                      "(username, password, Fname, Lname, email) "
                      "VALUES ('" + insertFormattingCharacters(username) + "','" +
                      insertFormattingCharacters(password) + "','" + insertFormattingCharacters(fname) +
                      "','" + insertFormattingCharacters(lname) + "','" + insertFormattingCharacters(email) + "');";

        if(!_query->exec(qry))
        {
            qDebug() << _query->lastError().text();
        }
        else
        {
            succeeded = true;
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to create user.";
    }

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

int mediaDatabase::getArtistId(const QString & artistName)
{
    bool ok = _db.open();
    int id = -1;

    if(ok)
    {
        QString artist = insertFormattingCharacters(artistName);

        if(!_query->exec("SELECT `id` FROM `Media_Player`.`Artist` WHERE name='" + artist + "';"))
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
        qDebug() << "Could not open database to get Artist ID";
    }

    return id;
}

int mediaDatabase::getAlbumId(const QString &artistName, const QString &albumTitle)
{
    bool ok = _db.open();
    int id = -1;

    if(ok)
    {\
        const QString album = insertFormattingCharacters(albumTitle);
        const int artistId = getArtistId(artistName);

        if(!_query->exec("SELECT id FROM `Media_Player`.`Album` WHERE Title='" + album + "' AND Artist_id=" + artistId + ");"))
        {
           qDebug() << _query->lastError().text();
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
        qDebug() << "Could not open database to get Album ID";
    }

    return id;
}

int mediaDatabase::getSongId(const QString &artistName, const QString &albumTitle, const QString &songTitle)
{
    bool ok = _db.open();
    int id = -1;

    if(ok)
    {\
        const QString song = insertFormattingCharacters(songTitle);
        const int albumId = getAlbumId(artistName,albumTitle);

        if(!_query->exec("SELECT id FROM `Media_Player`.`Song` WHERE Title='" + song + "' AND Album_id=" + albumId + ");"))
        {
            qDebug() << _query->lastError().text();
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
        qDebug() << "Could not open database to get Song ID";
    }

    return id;
}
