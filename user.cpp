#include "user.h"
#include <QCryptographicHash>
#include <QDebug>

user::user(QObject *parent) : QObject(parent),
  _username("Guest"),
  _pass(QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512)),
  _joinDateTime(QDateTime::currentDateTime())
{

}

user::~user()
{

}

const QString & user::getUsername()
{
    return _username;
}

const QString user::getJoinDateTime()
{
    return _joinDateTime.toString("yyyy-MM-dd hh:mm:ss");
}

void user::setMediaDatabase(mediaDatabase *database)
{
    _db = database;
}
