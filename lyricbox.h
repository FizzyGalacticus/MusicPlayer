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
    void lyricsChanged(const QString lyrics);

public slots:
    void getLyrics(QString, QString);
    void _lyricsRetrieved(QNetworkReply *);

private slots:
    void copyLyricsToClipboard();

private:
    QTextEdit * _lyricsTextBox;
    QLabel * _retrievedFromSiteLabel;
    QNetworkAccessManager * _networkManager;
    QString _artist, _title;

    const QString removePrecedingThe(const QString &);
    void formatLyricsUrlStringMetro(QString &);
};

#endif // LYRICBOX_H
