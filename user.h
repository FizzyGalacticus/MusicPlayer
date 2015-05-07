#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QDateTime>

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QObject *parent = 0);
    ~user();

signals:

public slots:

private:
    QString _username, _pass;
    QDateTime _joinDateTime;
};

#endif // USER_H
