#include "mediadatabase.h"
#include <QDebug>
#include <QSqlError>

mediaDatabase::mediaDatabase(QObject *parent) :
    QObject(parent),
    _db(new QSqlDatabase),
    _query(new QSqlQuery(*_db))
{
    _db->addDatabase("QMYSQL",tr("Media Player"));
    _db->setPort(3307);
    _db->setHostName("127.0.0.1");
    _db->setUserName("root");
    _db->setPassword("rootpass");

    bool ok = _db->open();

    if(ok)
    {
        qDebug() << "Database opened!";

        if(!_query->exec("CREATE DATABASE IF NOT EXISTS `Foo`;"))
            qDebug() << "Could not create database 'Foo'";
        if(!_query->exec("USE `Foo`;"))
            qDebug() << "Couldn't switch to database 'Test'";
        if(!_query->exec("CREATE TABLE IF NOT EXISTS `Foo`.`Artist` (Name VARCHAR(45) PRIMARY KEY, `# of Albums` INT);"))
            qDebug() << "Could not create table `Foo`.'Artist'";

        _db->close();
    }
    else
    {
        qDebug() << "Could not open database!";
        qDebug() << "Error:" << _db->lastError().text();
    }
}

mediaDatabase::~mediaDatabase()
{

}

