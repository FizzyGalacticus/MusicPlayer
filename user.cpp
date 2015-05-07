#include "user.h"
#include <QCryptographicHash>
#include <QDebug>

user::user(QObject *parent) : QObject(parent),
  _username("Guest"),
  _pass(QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512)),
  _joinDateTime(QDateTime::currentDateTime())
{
    qDebug() << _username << _pass << _joinDateTime.toString("yyyy-MM-dd hh:mm:ss");

    qDebug() << _pass.length();

    qDebug() << QCryptographicHash::hash("foo", QCryptographicHash::Sha3_512).length();

    qDebug() << (_pass == QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512));

    for(int i = 1; i < 1000; i++)
    {
        QString foo = "";
        for(int j = 0; j < i; j++)
            foo += "k";

        qDebug() << QCryptographicHash::hash(foo.toStdString().c_str(), QCryptographicHash::Sha3_512).length();
    }
}

user::~user()
{

}

