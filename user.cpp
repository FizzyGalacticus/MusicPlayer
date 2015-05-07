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
    _usernameLine(new QLineEdit("Username")),
    _passwordLine(new QLineEdit("Password")),
    _repeatPasswordLine(new QLineEdit("Repeat Password")),
    _firstNameLine(new QLineEdit("First Name")),
    _lastNameLine(new QLineEdit("Last Name")),
    _emailLine(new QLineEdit("youremail@example.com")),
    _db(database)
{
    prepareLoginLayout();
}

UserLoginDialog::~UserLoginDialog()
{

}

void UserLoginDialog::loginButtonHasBeenClicked()
{
    const QVector<QString> * results = _db->login(_usernameLine->text(),QCryptographicHash::hash(_passwordLine->text().toStdString().c_str(), QCryptographicHash::Sha3_512));
    if(results->size())
    {
        qDebug() << "Logged in!";
    }
    else
    {
        qDebug() << "Could not log in.";
    }
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

    QPushButton * loginButton = new QPushButton("Login");
    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginButtonHasBeenClicked()));

    //Set loginButton default width
    loginButton->setMaximumWidth(40);

    //Put stuff in layouts
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(_usernameLine);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(_passwordLine);
    loginButtonLayout->addSpacerItem(new QSpacerItem(20,20));
    loginButtonLayout->addWidget(loginButton);

    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(loginButtonLayout);

    this->setLayout(mainLayout);
}
