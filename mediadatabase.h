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

signals:

public slots:

private:
    QSqlDatabase _db;
    QSqlQuery * _query;

    void initiateSchema();
};

#endif // MEDIADATABASE_H
