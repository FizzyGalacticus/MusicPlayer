#ifndef LYRICBOX_H
#define LYRICBOX_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QNetworkAccessManager>

class lyricBox : public QWidget
{
    Q_OBJECT
public:
    explicit lyricBox(QWidget *parent = 0);

signals:

public slots:
    void getLyrics(QString, QString);

private:
    QTextEdit * _lyricsTextBox;
    QLabel * _retrievedFromSiteLabel;
    QNetworkAccessManager * _networkManager;
    QString _artist, _title;

    const QString removePrecedingThe(const QString &);
    void formatLyricsUrlStringMetro(QString &);
    void _lyricsRetrieved(QNetworkReply *);
};

#endif // LYRICBOX_H
