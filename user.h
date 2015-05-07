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

private slots:
    bool login(const QString username, const QString password);

private:
    QString _username;
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
    bool login(const QString username, const QString password);

public slots:

private slots:
    void loginButtonHasBeenClicked();

private:
    QLineEdit * _usernameLine, * _passwordLine, _repeatPasswordLine, _firstNameLine, _lastNameLine, _emailLine;
    mediaDatabase * _db;

    void prepareLoginLayout();
};

#endif // USER_H
