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
            qDebug() << "Could not open media_player database!";
        if(!checkIfValueExists("Artist","name",newArtist))
        {
            if(!_query->exec("INSERT INTO `Media_Player`.`Artist` VALUES ('" + newArtist + "');"))
                qDebug() << "Could not add new artist!";
            else
            {
                qDebug() << "New artist added!";
                succeeded = true;
            }
        }

        _db.close();
    }
    else
    {
        qDebug() << "Could not open database to add new artist.";
    }

    return succeeded;
}

bool mediaDatabase::addAlbum(const QString &artist, const QString &album)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
         QString qry = "INSERT INTO `Media_Player`.`Album` "
                "(Title, Artist_name) VALUES (':album', ':artist');";
        qry.replace(":album", album);
        qry.replace(":artist", artist);

        qDebug() << "Inserting into album:" << qry;

        if(!_query->exec(qry))
            qDebug() << "Could not add album!" << _query->lastError().text();
        else qDebug() << "Added album!";

        _db.close();
    }
    else
    {
        qDebug() << "Could not open datase to add album.";
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

        qDebug() << "Inserting into song:" << qry;

        if(!_query->exec(qry))
        {
            qDebug() << "Could not add song!" << _query->lastError().text() << "";
        }
        else succeeded = true;
    }
    else
    {
        qDebug() << "Could not open database to insert new song!";
    }

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
                "AND `Title` = ':title';";
        qry.replace(":artist", artist);
        qry.replace(":album", album);
        qry.replace(":song", song);

        if(!_query->exec(qry))
            qDebug() << "Could not increment song listens!" << _query->lastError().text();
        else
        {
            qDebug() << "Incremented song listens!";
            succeeded = true;
        }

        _db.close();
    }
    else qDebug() << "Could not open database to increment song counter!";

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
                if(!_query->exec(schemaFile->readAll().toStdString().c_str()))
                    qDebug() << "Could not initiate schema!";
                else qDebug() << "Created schema.";
                schemaFile->close();
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
        else qDebug() << "`Media_Player`.`" + tableName + "`.`" + columnName + "` contains \"" + value + "\"";
    }

    return exists;
}

const QString mediaDatabase::insertFormattingCharacters(const QString &str) const
{
    QString newStr = str;
    newStr.replace("'","\\'");
    newStr.replace("\"","\\\"");

    return newStr;
}
