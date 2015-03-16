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
    void valueChanged(int);

public slots:

private slots:
    void progressBarValueChanged(int);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    QProgressBar * _progressBar;
};

#endif // PROGRESSBAR_H
