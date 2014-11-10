#include <Python.h>
#include <mainwindow.h>
#include <QString>

const QString * MainWindow::getSongLyrics(const QString &artist, const QString &song)
{
    QString pyGetLyrics =
    "import urllib\n\
    def getLyrics(artist, song):\n\
        beginTag = '<!-- start of lyrics -->'\n\
        endTag = '<!-- end of lyrics -->'\n\
        url = 'http://www.azlyrics.com/lyrics/%s/%s.html' % (artist.replace(' ','').lower(), song.replace(' ','').lower())\n\
        page = urllib.urlopen(url).read()\n\
        lyrics = page[page.find(beginTag)+len(beginTag):page.find(endTag)].replace('<br />','')\n\
        thingsToLookFor = ['=']\n\
        for thing in thingsToLookFor:\n\
            if lyrics.find(thing) > -1:\n\
                lyrics = 'No lyrics available.'\n\
        return lyrics";

    QString pyCommand = "lyrics = getLyrics('";
    pyCommand += artist + "','";
    pyCommand += song + "')";

    /*Py_Initialize();
    PyRun_SimpleString(pyGetLyrics.toStdString().c_str());
    PyRun_SimpleString(pyCommand.toStdString().c_str());

    PyObject *pyMainModule = PyImport_AddModule("__main__");
    PyObject *v = PyObject_GetAttrString(pyMainModule, "lyrics");
    QString *lyrics = new QString(PyString_AsString(v));
    Py_Finalize();

    return lyrics;*/
    return new QString;
}
