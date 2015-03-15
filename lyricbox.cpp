#include "lyricbox.h"
#include <QVBoxLayout>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>

lyricBox::lyricBox(QWidget *parent) :
    QWidget(parent),
    _lyricsTextBox(new QTextEdit),
    _retrievedFromSiteLabel(new QLabel),
    _networkManager(new QNetworkAccessManager),
    _artist(""),
    _title("")
{
    connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_lyricsRetrieved(QNetworkReply*)));

    _lyricsTextBox->setAcceptDrops(false);
    _lyricsTextBox->setReadOnly(true);

    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(_lyricsTextBox);
    centralLayout->addWidget(_retrievedFromSiteLabel);
}

void lyricBox::getLyrics(QString artist, QString title)
{
    _artist = artist;
    _title = title;

    formatLyricsUrlStringMetro(artist);
    formatLyricsUrlStringMetro(title);

    QString urlString = "http://www.metrolyrics.com/" + title + "-lyrics-" + artist + ".html";

    _networkManager->get(QNetworkRequest(QUrl(urlString.toLower())));
}

const QString lyricBox::removePrecedingThe(const QString &str)
{
    QString retStr = "";
    if(str.left(3).toLower() == "the")
            retStr = str.right(str.size()-4);

    return retStr;
}

void lyricBox::formatLyricsUrlStringMetro(QString & str)
{
    for(auto i : str)
    {
        switch(i.toLatin1())
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
                str.remove(i);
            break;
        }
    }

    str.replace(" ", "-");
    str.replace('&',"and");
}

void lyricBox::_lyricsRetrieved(QNetworkReply * response)
{
    QString beginTag = "<p class='verse'>";
    QString endTag = "<div id=\"selected-song-meaning-open\" unselectable=\"on\" style=\"display:none;\">";
    QString page = QString(response->readAll());

    const int beginOfLyrics = page.indexOf(beginTag);
    const int endOfLyrics = page.indexOf(endTag,beginOfLyrics);

    QString lyrics = page.midRef(beginOfLyrics,endOfLyrics-beginOfLyrics).toString();

    if(lyrics == "") lyrics = "No lyrics available.";

    _lyricsTextBox->setText(lyrics);
    _retrievedFromSiteLabel->setText("Lyrics retrieved from: Metrolyrics.com");
}
