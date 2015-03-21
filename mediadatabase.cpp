#include "mediadatabase.h"

mediaDatabase::mediaDatabase(QObject *parent) :
    QObject(parent),
    _db(new QSqlDatabase("QMYSQL")),
    _query(new QSqlQuery(*_db))
{

}

mediaDatabase::~mediaDatabase()
{

}

