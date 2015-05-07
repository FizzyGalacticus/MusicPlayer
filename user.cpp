#include "user.h"
#include <QCryptographicHash>
#include <QDebug>

User::User(QObject *parent) : QObject(parent),
  _username("Guest"),
  _pass(QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512)),
  _joinDateTime(QDateTime::currentDateTime())
{

}

User::~User()
{

}

const QString & User::getUsername()
{
    return _username;
}

const QString User::getJoinDateTime()
{
    return _joinDateTime.toString("yyyy-MM-dd hh:mm:ss");
}

void User::setMediaDatabase(mediaDatabase *database)
{
    _db = database;
}
