#include <mainwindow.h>
#include <QString>
#include <QDebug>
#include <QNetworkReply>
#include <QUrl>

void MainWindow::updateSongLyrics(QString artist, QString song)
{
    if(artist.left(3).toLower() == "the")
        artist = artist.right(artist.size()-4);

    formatLyricsUrlString(artist);
    formatLyricsUrlString(song);
    QString urlString = "http://www.metrolyrics.com/" + song + "-lyrics-" + artist + ".html";

    qDebug() << "Attempting to get lyrics from:" << urlString.toLower();

    _networkManager->get(QNetworkRequest(QUrl(urlString.toLower())));
}

void MainWindow::formatLyricsUrlString(QString & str)
{
    for(QString::Iterator i = str.begin(); i < str.end(); i++)
    {\
        switch(i->toLatin1())
        {
            case '-':
            case ',':
            case '\'':
            case '!':
            case '(':
            case ')':
            case '/':
            case '.':
            case '?':
                str.remove(*i);
            break;
        }
    }

    str.replace(" ", "-");
    str.replace('&',"and");
}

void MainWindow::_lyricsRetrieved(QNetworkReply * response)
{
    QString beginTag = "<p class='verse'>";
    QString endTag = "<div id=\"selected-song-meaning-open\" unselectable=\"on\" style=\"display:none;\">";
    QString page = QString(response->readAll());

    const int beginOfLyrics = page.indexOf(beginTag);
    const int endOfLyrics = page.indexOf(endTag,beginOfLyrics);

    QString lyrics = page.midRef(beginOfLyrics,endOfLyrics-beginOfLyrics).toString();

    if(lyrics == "") lyrics = "No lyrics available.";

    _lyricsTextBox->setText(lyrics);
}
