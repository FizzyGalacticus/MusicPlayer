#ifndef MEDIADATABASE_H
#define MEDIADATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class mediaDatabase : public QObject
{
    Q_OBJECT
public:
    explicit mediaDatabase(QObject *parent = 0);
    ~mediaDatabase();

    bool addSong(const QString & songTitle, const QString & albumTitle, const QString & artistName);
    bool addLyrics(const QString & artistName, const QString & songTitle, const QString & lyrics);
    bool incrementSongCounter(const QString & songTitle, const QString & albumTitle, const QString & artistName);

signals:

public slots:

private:
    QSqlDatabase _db;
    QSqlQuery * _query;

    void initiateSchema();
    bool checkIfValueExists(const QString & tableName, const QString & columnName, const QString & value);
    const QString insertFormattingCharacters(const QString & str) const;
    int getArtistId(const QString & artistName);
    int getAlbumId(const QString & artistName, const QString & albumTitle);
    int getSongId(const QString & artistName, const QString & albumTitle, const QString & songTitle);
    bool addArtist(const QString & newArtist);
    bool addAlbum(const int & artistId, const QString & album);
};

#endif // MEDIADATABASE_H
