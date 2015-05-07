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
  _firstName(""),
  _lastName(""),
  _email(""),
  _joinDateTime(QDateTime::currentDateTime()),
  _db(NULL)
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

void User::presentLoginWindow()
{
    if(_db != NULL)
    {
        UserLoginDialog login(_db);
        connect(&login, SIGNAL(userDataReceived(const QString &, const QString &,
                                                const QString &, const QString &,
                                                const QString &)),
                               this, SLOT(userDataReceived(const QString & , const QString & ,
                                                           const QString & , const QString & ,
                                                           const QString & )));
        login.exec();
    }
}

void User::presentCreateUserWindow()
{
    if(_db != NULL)
    {
        CreateUserDialog create(_db);
        connect(&create, SIGNAL(userDataReceived(const QString, const QString, const QString, const QString)),
                this, SLOT(userDataReceived(const QString, const QString, const QString, const QString)));
        create.exec();
    }
}

void User::presentUserInformationWindow()
{
    const QString joinDateTime = _joinDateTime.toString("dddd, MMMM dd, yyyy");
    UserInformation userInfo(_username, _firstName + " " + _lastName, _email, joinDateTime);
    userInfo.exec();
}

void User::userDataReceived(const QString & username, const QString &firstName, const QString &lastName, const QString &email, const QString & joinDateTime)
{
    _username = username;
    _firstName = firstName;
    _lastName = lastName;
    _email = email;
    _joinDateTime = QDateTime::fromString(joinDateTime, "yyyy-MM-dd hh:mm:ss");

    qDebug() << joinDateTime << _joinDateTime.toString();
}

UserLoginDialog::UserLoginDialog(mediaDatabase *database, QWidget *parent) : QDialog(parent),
    _usernameLine(new QLineEdit("")),
    _passwordLine(new QLineEdit("")),
    _db(database)
{
    prepareLoginLayout();
    this->setWindowTitle("Login");

    _usernameLine->setPlaceholderText("Username");
    _passwordLine->setPlaceholderText("Password");

    _passwordLine->setEchoMode(QLineEdit::Password);
}

UserLoginDialog::~UserLoginDialog()
{

}

void UserLoginDialog::loginButtonHasBeenClicked()
{
    const QVector<QString> * results = _db->login(_usernameLine->text(),
                                                  QCryptographicHash::hash(_passwordLine->text().toStdString().c_str(),
                                                                           QCryptographicHash::Sha3_512)
                                                  );

    if(results->size())
    {
        QString fname = results->at(0), lname = results->at(1), email = results->at(2), joinDateTime = results->at(3);

        emit userDataReceived(_usernameLine->text(), fname, lname, email, joinDateTime);
        this->close();
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

CreateUserDialog::CreateUserDialog(mediaDatabase *database, QWidget *parent) : QDialog(parent),
    _usernameLine(new QLineEdit("")),
    _passwordLine(new QLineEdit("")),
    _repeatPasswordLine(new QLineEdit("")),
    _firstNameLine(new QLineEdit("")),
    _lastNameLine(new QLineEdit("")),
    _emailLine(new QLineEdit("")),
    _db(database),
    _usernameAvailableLabel(new QLabel)
{
    prepareCreationLayout();
    this->setWindowTitle("Create User");

    _usernameLine->setPlaceholderText("Username");
    _passwordLine->setPlaceholderText("Password");
    _repeatPasswordLine->setPlaceholderText("Repeat password");
    _firstNameLine->setPlaceholderText("First Name");
    _lastNameLine->setPlaceholderText("Last Name");
    _emailLine->setPlaceholderText("youremail@example.ninja");

    _passwordLine->setEchoMode(QLineEdit::Password);
    _repeatPasswordLine->setEchoMode(QLineEdit::Password);
}

CreateUserDialog::~CreateUserDialog()
{

}

void CreateUserDialog::checkUsernameButtonHasBeenClicked()
{
    if(_db->userExists(_usernameLine->text()) || _usernameLine->text() == "")
    {
        _usernameAvailableLabel->setText(QString("<html>&#x2716;</html>"));
        _usernameAvailableLabel->setStyleSheet("QLabel {color: red;}");
    }
    else
    {
        _usernameAvailableLabel->setText(QString("<html>&#x2714;</html>"));
        _usernameAvailableLabel->setStyleSheet("QLabel {color: green;}");
    }
}

void CreateUserDialog::createUserButtonHasBeenClicked()
{
    if(passwordsAreEqual() && usernameNotEmpty())
    {
        const QString joinDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if(_db->createUser(_usernameLine->text(),
                        QCryptographicHash::hash(_passwordLine->text().toStdString().c_str(), QCryptographicHash::Sha3_512),
                        _firstNameLine->text(),
                        _lastNameLine->text(),
                        _emailLine->text(),
                        joinDateTime))
        {
            emit userDataReceived(_usernameLine->text(), _firstNameLine->text(), _lastNameLine->text(), _emailLine->text(), joinDateTime);
        }

        this->close();
    }
    else
    {

    }
}

void CreateUserDialog::prepareCreationLayout()
{
    //Initialize layouts
    QHBoxLayout * usernameLayout = new QHBoxLayout;
    QHBoxLayout * passwordLayout = new QHBoxLayout;
    QHBoxLayout * repeatPasswordLayout = new QHBoxLayout;
    QHBoxLayout * fNameLayout = new QHBoxLayout;
    QHBoxLayout * lNameLayout = new QHBoxLayout;
    QHBoxLayout * emailLayout = new QHBoxLayout;
    QHBoxLayout * createUserButtonLayout = new QHBoxLayout;

    QVBoxLayout * mainLayout = new QVBoxLayout;

    //Initialize objects needed
    QLabel * usernameLabel = new QLabel("Username:");
    QLabel * passwordLabel = new QLabel("Password:");
    QLabel * repeatPasswordLabel = new QLabel("Repeat Password:");
    QLabel * fNameLabel = new QLabel("First Name:");
    QLabel * lNameLabel = new QLabel("Last Name:");
    QLabel * emailLabel = new QLabel("Email:");

    QPushButton * checkUsernameButton = new QPushButton("Check It!");
    connect(checkUsernameButton, SIGNAL(clicked()), this, SLOT(checkUsernameButtonHasBeenClicked()));
    QPushButton * createUserButton = new QPushButton("Create");
    connect(createUserButton, SIGNAL(clicked()), this, SLOT(createUserButtonHasBeenClicked()));

    //Set widths for buttons
    checkUsernameButton->setMaximumWidth(60);
    createUserButton->setMaximumWidth(50);

    //Put stuff in layouts
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(_usernameLine);
    usernameLayout->addWidget(checkUsernameButton);
    usernameLayout->addWidget(_usernameAvailableLabel);

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(_passwordLine);

    repeatPasswordLayout->addWidget(repeatPasswordLabel);
    repeatPasswordLayout->addWidget(_repeatPasswordLine);

    fNameLayout->addWidget(fNameLabel);
    fNameLayout->addWidget(_firstNameLine);

    lNameLayout->addWidget(lNameLabel);
    lNameLayout->addWidget(_lastNameLine);

    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(_emailLine);

    createUserButtonLayout->addWidget(createUserButton);

    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(repeatPasswordLayout);
    mainLayout->addLayout(fNameLayout);
    mainLayout->addLayout(lNameLayout);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(createUserButtonLayout);

    this->setLayout(mainLayout);
}

bool CreateUserDialog::passwordsAreEqual()
{
    return (_passwordLine->text() == _repeatPasswordLine->text());
}

bool CreateUserDialog::usernameNotEmpty()
{
    return _usernameLine->text().size();
}

UserInformation::UserInformation(const QString username, const QString name,
                                 const QString email, const QString membersince, QWidget *parent) :
    QDialog(parent),
    _username(username),
    _name(name),
    _email(email),
    _membersince(membersince)
{
    prepareUserInfoLayout();
    this->setWindowTitle("User Info");
}

UserInformation::~UserInformation()
{

}

void UserInformation::okButtonHasBeenPressed()
{
    this->close();
}

void UserInformation::prepareUserInfoLayout()
{
    //Initialize Layouts
    QHBoxLayout * usernameLayout = new QHBoxLayout;
    QHBoxLayout * nameLayout = new QHBoxLayout;
    QHBoxLayout * emailLayout = new QHBoxLayout;
    QHBoxLayout * membersinceLayout = new QHBoxLayout;
    QHBoxLayout * okButtonLayout = new QHBoxLayout;

    QVBoxLayout * mainLayout = new QVBoxLayout;

    //Initialize Objects Needed
    QLabel * usernameLabel = new QLabel("Username: " + _username);
    QLabel * nameLabel = new QLabel("Name: " + _name);
    QLabel * emailLabel = new QLabel("Email: " + _email);
    QLabel * membersinceLabel = new QLabel("Member Since: " + _membersince);

    QPushButton * okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonHasBeenPressed()));

    //Put stuff in layouts
    usernameLayout->addWidget(usernameLabel);
    nameLayout->addWidget(nameLabel);
    emailLayout->addWidget(emailLabel);
    membersinceLayout->addWidget(membersinceLabel);
    okButtonLayout->addWidget(okButton);

    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(membersinceLayout);
    mainLayout->addLayout(okButtonLayout);

    this->setLayout(mainLayout);
}
