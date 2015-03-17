#include "videowidget.h"
#include <QMouseEvent>
#include <QKeyEvent>

videoWidget::videoWidget(QVideoWidget * parent) :
    QVideoWidget(parent)
{

}

videoWidget::~videoWidget()
{

}

void videoWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    if(isFullScreen())
        setFullScreen(false);
    else setFullScreen(true);
}

void videoWidget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Escape)
        if(isFullScreen())
            setFullScreen(false);
}
