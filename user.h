#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include "mediadatabase.h"

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QObject *parent = 0);
    ~user();

    const QString & getUsername();
    const QString getJoinDateTime();
    void setMediaDatabase(mediaDatabase * database);

signals:

public slots:

private:
    QString _username, _pass;
    QDateTime _joinDateTime;

    mediaDatabase * _db;
};

#endif // USER_H
