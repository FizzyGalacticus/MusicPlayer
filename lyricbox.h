#ifndef LYRICBOX_H
#define LYRICBOX_H

#include <QWidget>
#include <QTextEdit>

class lyricBox : public QWidget
{
    Q_OBJECT
public:
    explicit lyricBox(QWidget *parent = 0);

signals:

public slots:

private:
    QTextEdit * _lyricsTextBox;
};

#endif // LYRICBOX_H
