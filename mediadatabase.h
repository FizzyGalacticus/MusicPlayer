#ifndef MEDIADATABASE_H
#define MEDIADATABASE_H

#include <QObject>

class mediaDatabase : public QObject
{
    Q_OBJECT
public:
    explicit mediaDatabase(QObject *parent = 0);
    ~mediaDatabase();

signals:

public slots:
};

#endif // MEDIADATABASE_H
