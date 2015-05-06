#ifndef USER_H
#define USER_H

#include <QObject>

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QObject *parent = 0);
    ~user();

signals:

public slots:
};

#endif // USER_H
