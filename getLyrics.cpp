#include <Python.h>
#include <mainwindow.h>
#include <QString>
#include <QDebug>

void MainWindow::updateSongLyrics(const QString & artist, const QString & song)
{
    _lyricsTextBox->setText(*getSongLyrics(removeUnwantedCharacters(artist),removeUnwantedCharacters(song)));
}

const QString MainWindow::removeUnwantedCharacters(QString str)
{
    for(QString::Iterator i = str.begin(); i < str.end(); i++)
        if(*i == ' ' || *i == ',' || *i == '\'' || *i == '-' || *i == '!' || *i == '(' || *i == ')')
            str.remove(*i);

    return str;
}

QString * MainWindow::getSongLyrics(const QString & artist, const QString & song)
{
    QString pyGetLyrics =
"import urllib\n\
def getLyrics(artist, song):\n\
    beginTag = '<!-- start of lyrics -->'\n\
    endTag = '<!-- end of lyrics -->'\n\
    if artist[0:3].lower() == 'the':\n\
        artist = artist[3:]\n\
    artist = artist.lower()\n\
    song = song.lower()\n\
    url = 'http://www.azlyrics.com/lyrics/%s/%s.html' % (artist, song)\n\
    print 'Attempting to pull lyrics from %s' % url\n\
    page = urllib.urlopen(url).read()\n\
    lyrics = page[page.find(beginTag)+len(beginTag):page.find(endTag)].replace('<br />','')\n\
    thingsToLookFor = ['=']\n\
    for thing in thingsToLookFor:\n\
        if lyrics.find(thing) > -1:\n\
            lyrics = 'No lyrics available.'\n\
    if lyrics == 'No lyrics available.':\n\
        print 'No lyrics found!'\n\
    else:\n\
        print 'Lyrics found!'\n\
    return lyrics";

    QString pyCommand = "lyrics = getLyrics('";
    pyCommand += artist + "','";
    pyCommand += song + "')";

    Py_Initialize();
    PyRun_SimpleString(pyGetLyrics.toStdString().c_str());
    PyRun_SimpleString(pyCommand.toStdString().c_str());

    PyObject *pyMainModule = PyImport_AddModule("__main__");
    PyObject *v = PyObject_GetAttrString(pyMainModule, "lyrics");
    QString *lyrics = new QString(PyString_AsString(v));
    Py_Finalize();

    return lyrics;
}
