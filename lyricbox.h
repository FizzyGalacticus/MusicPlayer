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
    void setFont(const QFont &);

signals:
    void lyricsChanged(const QString lyrics);

public slots:
    void retrieveLyrics(QString, QString);
    void lyricsRetrieved(QNetworkReply *);

private slots:
    void copyLyricsToClipboard();
    void copySelectedToClipboard();

private:
    QTextEdit * _lyricsTextBox;
    QLabel * _retrievedFromSiteLabel;
    QNetworkAccessManager * _networkManager;
    QString _artist, _title;

    const QString removePrecedingThe(const QString &);
    void formatLyricsUrlStringMetro(QString &);
};

#endif // LYRICBOX_H
