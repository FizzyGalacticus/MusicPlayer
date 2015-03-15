#include "lyricbox.h"
#include <QVBoxLayout>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAction>
#include <QClipboard>
#include <QApplication>

lyricBox::lyricBox(QWidget *parent) :
    QWidget(parent),
    _lyricsTextBox(new QTextEdit("Lyrics will show here as available.")),
    _retrievedFromSiteLabel(new QLabel),
    _networkManager(new QNetworkAccessManager),
    _artist(""),
    _title("")
{
    connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_lyricsRetrieved(QNetworkReply*)));

    _lyricsTextBox->setAcceptDrops(false);
    _lyricsTextBox->setReadOnly(true);

    QAction * copyText = new QAction(QString(tr("Copy Lyrics")), this);

    connect(copyText, SIGNAL(triggered()), this, SLOT(copyLyricsToClipboard()));

    _lyricsTextBox->addAction(copyText);
    _lyricsTextBox->setContextMenuPolicy(Qt::ActionsContextMenu);

    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(_lyricsTextBox);
    centralLayout->addWidget(_retrievedFromSiteLabel);

    this->setLayout(centralLayout);
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
    QString beginTag = "<div id=\"lyrics-body-text\">";
    QString endTag = "</div>";
    QString page = QString(response->readAll());

    const int beginOfLyrics = page.indexOf(beginTag);
    const int endOfLyrics = page.indexOf(endTag,beginOfLyrics+1);

    QString lyrics = page.midRef(beginOfLyrics,endOfLyrics-beginOfLyrics).toString();

    if(lyrics == "") lyrics = "No lyrics available.";

    _lyricsTextBox->setText(lyrics);
    _retrievedFromSiteLabel->setText("Lyrics retrieved from: Metrolyrics.com");
}

void lyricBox::copyLyricsToClipboard()
{
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setText(_lyricsTextBox->toPlainText());
}
