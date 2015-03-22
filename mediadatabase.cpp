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
        if(!_query->exec("USE media_player;"))
            qDebug() << "Could not open media_player database!";
        if(!checkIfValueExists("artist","name",newArtist))
        {
            if(!_query->exec("INSERT INTO `media_player`.`artist` VALUES ('" + newArtist + "');"))
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

bool mediaDatabase::addAlbum(const QString &artist, const QString &album, const QByteArray *albumCover)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        if(!checkIfValueExists("album","Artist_name",artist) && !checkIfValueExists("album","Title",album))
        {
            QString qry = "INSERT INTO `Media_Player`.`album` (Title, AlbumCover, Artist_name) VALUES ('";
            qry += album + "', " + *albumCover + ", '" + artist + "');";
            if(!_query->exec(qry))
                qDebug() << "Could not add album!";
            else qDebug() << "Added album!";
        }
    }
    else
    {
        qDebug() << "Could not open datase to add album.";
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

    if(!_query->exec("SELECT COUNT(*) FROM `media_player`.`" + tableName + "` WHERE `" + columnName + "`='" + value + "';"))
        qDebug() << "Could not check the existence of" << value;
    else
    {
        _query->next();
        if(!_query->value(0).toBool()) exists = false;
        else qDebug() << "`media_player`.`" + tableName + "`.`" + columnName + "` contains \"" + value + "\"";
    }

    return exists;
}
