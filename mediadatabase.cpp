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
        if(!_query->exec("SELECT COUNT(*) FROM artist WHERE name='" + newArtist + "';"))
            qDebug() << "Could not check if artist exists!";
        else
        {
            _query->next();
            if(_query->value(0).toInt() == 0)
            {
                if(!_query->exec("INSERT INTO `media_player`.`artist` VALUES ('" + newArtist + "');"))
                    qDebug() << "Could not add new artist!";
                else
                {
                    qDebug() << "New artist added!";
                    succeeded = true;
                }
            }
        }
    }
    else
    {
        qDebug() << "Could not open database to add new artist.";
    }

    _db.close();
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
