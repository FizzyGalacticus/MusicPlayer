#include "lyricbox.h"
#include <QVBoxLayout>

lyricBox::lyricBox(QWidget *parent) :
    QWidget(parent),
    _lyricsTextBox(new QTextEdit)
{
    _lyricsTextBox->setAcceptDrops(false);
    _lyricsTextBox->setReadOnly(true);

    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(_lyricsTextBox);
}
