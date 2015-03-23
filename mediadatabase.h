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

    bool addArtist(const QString & newArtist);
    bool addAlbum(const QString & artist, const QString & album);
    bool addSong(const QString & songTitle, const QString & albumTitle, const QString & artistName);

signals:

public slots:

private:
    QSqlDatabase _db;
    QSqlQuery * _query;

    void initiateSchema();
    bool checkIfValueExists(const QString & tableName, const QString & columnName, const QString & value);
    const QString insertFormattingCharacters(const QString & str) const;
};

#endif // MEDIADATABASE_H
