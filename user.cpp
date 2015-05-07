#include "user.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QDialog>

User::User(QObject *parent) : QObject(parent),
  _username("Guest"),
  _pass(QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512)),
  _joinDateTime(QDateTime::currentDateTime())
{

}

User::~User()
{

}

bool User::login(const QString username, const QString password)
{
    return false;
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

void User::presentLoginWindow()
{
    UserLoginDialog login;
    connect(&login,SIGNAL(login(QString,QString)), this, SLOT(login(QString,QString)));
    login.exec();
}

UserLoginDialog::UserLoginDialog(QWidget *parent) : QDialog(parent),
    _user("Username"),
    _pass("password"),
    _fname("First Name"),
    _lname("Last Name"),
    _email("youremail@example.com")
{

}

UserLoginDialog::~UserLoginDialog()
{

}
