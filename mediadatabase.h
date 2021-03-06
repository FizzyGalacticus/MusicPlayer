#ifndef MEDIADATABASE_H
#define MEDIADATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

class mediaDatabase : public QObject
{
    Q_OBJECT
public:
    explicit mediaDatabase(QObject *parent = 0);
    ~mediaDatabase();

    bool addSong(const QString & songTitle, const QString & albumTitle, const QString & artistName);
    bool addLyrics(const QString & artistName, const QString & songTitle, const QString & lyrics);
    bool incrementSongCounter(const QString & songTitle, const QString & artistName, const QString & username);
    const QVector<QString> * login(const QString & username, const QString & password);
    bool userExists(const QString & username);
    bool createUser(const QString & username, const QString & password, const QString & fname, const QString & lname, const QString & email, const QString &joinDateTime);
    const QVector<QString> * getFavoriteSong(const QString & username);
    const QVector<QString> * getFavoriteAlbum(const QString & username);
    const QVector<QString> * getFavoriteArtist(const QString & username);

signals:

public slots:

private:
    QSqlDatabase _db;
    QSqlQuery * _query;

    static const QString universalQuery;
    static const int universalSize;

    void initiateSchema();
    bool checkIfValueExists(const QString & tableName, const QString & columnName, const QString & value);
    const QString insertFormattingCharacters(const QString & str) const;
    int getArtistId(const QString & artistName);
    int getAlbumId(const QString & artistName, const QString & albumTitle);
    int getSongId(const QString & artistName, const QString & songTitle);
    int getUserId(const QString & username);
    bool addArtist(const QString & newArtist);
    bool addAlbum(const int & artistId, const QString & album);
};

#endif // MEDIADATABASE_H
