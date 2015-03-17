#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class videoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit videoWidget(QVideoWidget *parent = 0);
    ~videoWidget();

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private:

};

#endif // VIDEOWIDGET_H
