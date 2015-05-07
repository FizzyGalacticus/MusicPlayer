#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QDateTime>
#include "mediadatabase.h"
#include <QLineEdit>

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
    void presentLoginWindow();
    void presentCreateUserWindow();

private slots:
    void userDataReceived(const QString & firstName, const QString & lastName, const QString & email);

private:
    QString _username, _firstName, _lastName, _email;
    QDateTime _joinDateTime;

    mediaDatabase * _db;
};

class UserLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserLoginDialog(mediaDatabase * database, QWidget *parent = 0);
    ~UserLoginDialog();

signals:
    void userDataReceived(const QString & firstName, const QString & lastName, const QString & email);

public slots:

private slots:
    void loginButtonHasBeenClicked();

private:
    QLineEdit * _usernameLine, * _passwordLine;
    mediaDatabase * _db;

    void prepareLoginLayout();
};

class CreateUserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateUserDialog(mediaDatabase * database, QWidget *parent = 0);
    ~CreateUserDialog();

signals:

public slots:

private slots:

private:
    QLineEdit * _usernameLine, * _passwordLine, _repeatPasswordLine, _firstNameLine, _lastNameLine, _emailLine;
    mediaDatabase * _db;
};

#endif // USER_H
