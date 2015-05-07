#include "mediadatabase.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <QFile>
#include <QVector>
#include <QDateTime>

const QString mediaDatabase::universalQuery = "SELECT u.username AS `User`, `User ID`, `Artist`, `Artist ID`, `Album Title`, "
                             "`Album ID`, `Song Title`, `Song ID`, `Plays` FROM User u JOIN "
                             "(SELECT uhs.User_id AS `User ID`, `Artist`, `Artist ID`, `Album Title`, `Album ID`, "
                             "`Song Title`, `Song ID`, uhs.numberOfListens AS `Plays` FROM User_has_Song uhs "
                             "JOIN (SELECT ar.name AS `Artist`, `Artist ID`, `Album Title`, `Album ID`, `Song Title`, "
                             "`Song ID` FROM (SELECT s.Artist_id AS `Artist ID`, `Album Title`, `Album ID`, s.Title AS "
                             "`Song Title`, `Song ID` FROM (SELECT al.Title AS `Album Title`, al.id AS `Album ID`, "
                             "ahs.Song_id AS `Song ID` FROM Album al JOIN Album_has_Song ahs ON al.id=ahs.Album_id) AS f "
                             "JOIN Song s ON s.id=f.`Song ID`) AS g JOIN Artist ar ON ar.id=`Artist ID`) AS h ON "
                             "uhs.Song_id=`Song ID`) AS i ON u.id=`User ID`;";
const int mediaDatabase::universalSize = 9;

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

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString song = insertFormattingCharacters(songTitle);

        QString qry = "INSERT INTO `Media_Player`.`Song` "
                      "(Title, Artist_id) "
                      "VALUES (':song', ':artist');";
        qry.replace(":song", song);
        qry.replace(":artist", QString::number(artistId));

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else succeeded = true;

        _db.close();

        const int songId = getSongId(artistName,songTitle);
        const int albumId = getAlbumId(artistName,albumTitle);

        ok = _db.open();

        if(ok)
        {
            qry = "INSERT INTO `Media_Player`.`Album_has_Song` (Album_id, Song_id) "
                  "VALUES (" + QString::number(albumId) + "," + QString::number(songId) + ");";

            if(!_query->exec(qry))
                qDebug() << "Couldn't add song to album!";

            _db.close();
        }
        else
        {
            qDebug() << "Could not open database to add song to album.";
        }
    }
    else
    {
        qDebug() << "Could not open database to insert new song.";
    }

    return succeeded;
}

bool mediaDatabase::addLyrics(const QString & artistName, const QString & songTitle, const QString & newLyrics)
{
    QString lyrics = insertFormattingCharacters(newLyrics);

    const int songId = getSongId(artistName,songTitle);

    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "UPDATE `Media_Player`.`Song` "
                "SET `lyrics`=':lyrics' "
                "WHERE `id`=':song';";
        qry.replace(":lyrics", lyrics).replace(":song", QString::number(songId));

        if(!_query->exec(qry))
            qDebug() << "\n\nLAST ERROR: " << _query->lastQuery() << "\n\n";
        else succeeded = true;

        _db.close();
    }
    else qDebug() << "Could not open database to add lyrics for song:" << songTitle;

    return succeeded;
}

bool mediaDatabase::incrementSongCounter(const QString &songTitle, const QString &artistName, const QString & username)
{
    const int songId = getSongId(artistName, songTitle), userId = getUserId(username);
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "INSERT INTO `Media_Player`.`User_has_Song` "
                      "(User_id, Song_id) VALUES "
                      "(" + QString::number(userId) + "," + QString::number(songId) +
                      ");";

        if(!_query->exec(qry))
            qDebug() << "Couldn't add entry to User_has_Song";

        qry = "UPDATE `Media_Player`.`User_has_Song` "
                "SET `numberOfListens` = `numberOfListens` + 1 "
                "WHERE `User_id` = ':user' "
                "AND `Song_id` = ':song';";
        qry.replace(":user", QString::number(userId));
        qry.replace(":song", QString::number(songId));

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else    succeeded = true;

        _db.close();
    }
    else qDebug() << "Could not open database to increment listens for song:" << songTitle;

    return succeeded;
}

const QVector<QString> * mediaDatabase::login(const QString &username, const QString &password)
{
    bool ok = _db.open();
    QVector<QString> * results = new QVector<QString>;

    if(ok)
    {
        QString qry = "SELECT `fname`, `lname`, `email`, `joinDateTime` "
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

                results->push_back(_query->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
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

bool mediaDatabase::createUser(const QString &username, const QString &password,
                               const QString &fname, const QString &lname,
                               const QString &email, const QString &joinDateTime)
{
    bool ok = _db.open(), succeeded = false;

    if(ok)
    {
        QString qry = "INSERT INTO `Media_Player`.`User` "
                      "(username, password, Fname, Lname, email, joinDateTime) "
                      "VALUES ('" + insertFormattingCharacters(username) + "','" +
                      insertFormattingCharacters(password) + "','" + insertFormattingCharacters(fname) +
                      "','" + insertFormattingCharacters(lname) + "','" + insertFormattingCharacters(email) + "','" +
                      joinDateTime + "');";

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
    const int artistId = getArtistId(artistName);
    int id = -1;

    bool ok = _db.open();

    if(ok)
    {\
        const QString album = insertFormattingCharacters(albumTitle);

        QString qry = "SELECT `id` FROM `Media_Player`.`Album` "
                      "WHERE `Title`='" + album + "' "
                      "AND Artist_id=" + QString::number(artistId) + ";";

        if(!_query->exec(qry))
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

int mediaDatabase::getSongId(const QString &artistName, const QString &songTitle)
{
    const int artistId = getArtistId(artistName);

    int id = -1;

    bool ok = _db.open();

    if(ok)
    {\
        const QString song = insertFormattingCharacters(songTitle);

        QString qry = "SELECT `id` FROM `Media_Player`.`Song` "
                      "WHERE `Title`='" + song + "'" +
                      "AND `Artist_id`=" + QString::number(artistId) + ";";

        if(!_query->exec(qry))
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

int mediaDatabase::getUserId(const QString &username)
{
    int id = -1;
    bool ok = _db.open();

    if(ok)
    {
        QString qry = "SELECT `id` FROM `Media_Player`.`User` "
                      "WHERE `username`='" +
                      insertFormattingCharacters(username) + "';";

        qDebug() << qry;

        if(!_query->exec(qry))
            qDebug() << _query->lastError().text();
        else
        {
            _query->next();
            id = _query->value(0).toInt();
        }

        _db.close();
    }
    else
    {
        qDebug() << "Couldn't open database to get User ID.";
    }

    return id;
}
