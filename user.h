#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include "mediadatabase.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
    ~User();

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
