#include "user.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

User::User(QObject *parent) : QObject(parent),
  _username("Guest"),
  _pass(QCryptographicHash::hash("guest", QCryptographicHash::Sha3_512)),
  _joinDateTime(QDateTime::currentDateTime()),
  _db(NULL)
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
    if(_db != NULL)
    {
        UserLoginDialog login(_db);
        connect(&login,SIGNAL(login(QString,QString)), this, SLOT(login(QString,QString)));
        login.exec();
    }
}

UserLoginDialog::UserLoginDialog(mediaDatabase *database, QWidget *parent) : QDialog(parent),
    _user("Username"),
    _pass("password"),
    _fname("First Name"),
    _lname("Last Name"),
    _email("youremail@example.com"),
    _db(database)
{
    prepareLoginLayout();
}

UserLoginDialog::~UserLoginDialog()
{

}

void UserLoginDialog::prepareLoginLayout()
{
    //Initialize Layouts
    QHBoxLayout * usernameLayout = new QHBoxLayout;
    QHBoxLayout * passwordLayout = new QHBoxLayout;
    QHBoxLayout * loginButtonLayout = new QHBoxLayout;

    QVBoxLayout * mainLayout = new QVBoxLayout;

    //Initialize objects needed
    QLabel * usernameLabel = new QLabel("Username:");
    QLabel * passwordLabel = new QLabel("Password:");

    QLineEdit * usernameLine = new QLineEdit;
    QLineEdit * passwordLine = new QLineEdit;

    QPushButton * loginButton = new QPushButton("Login");

    //Set password field to password mode
    passwordLine->setEchoMode(QLineEdit::Password);

    //Set loginButton default width
    loginButton->setMaximumWidth(40);

    //Put stuff in layouts
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameLine);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLine);
    loginButtonLayout->addSpacerItem(new QSpacerItem(20,20));
    loginButtonLayout->addWidget(loginButton);

    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(loginButtonLayout);

    this->setLayout(mainLayout);
}
