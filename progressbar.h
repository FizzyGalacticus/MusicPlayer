#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>

class progressBar : public QWidget
{
    Q_OBJECT
public:
    explicit progressBar(QWidget *parent = 0);
    ~progressBar();

signals:

public slots:

private:
    QProgressBar * _progressBar;
};

#endif // PROGRESSBAR_H
