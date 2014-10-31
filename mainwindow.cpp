#include "actions.cpp"
#include "componentactions.cpp"
#include "menus.cpp"
#include "menuactions.cpp"
#include "setup.cpp"
#include "ui_mainwindow.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _mainWindowIcon(":/Resources/icons/mainWindowIcon.png"),
    _centralWidget(new QWidget(this)),
    _mainLayout(new QVBoxLayout(_centralWidget)),
    _isPlaying(false),
    _isShuffled(false),
    _prevButton(new QPushButton(this)),
    _prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    _playButton(new QPushButton(this)),
    _playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    _playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    _nextButton(new QPushButton(this)),
    _nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    _helpIcon(":/Resources/icons/Menu-Help-icon.png"),
    _infoIcon(":/Resources/icons/Menu-Info-icon.png"),
    _openIcon(":/Resources/icons/Menu-Open-icon.png"),
    _exitIcon(":/Resources/icons/Menu-Exit-icon.png"),
    _qtIcon(":/Resources/icons/Qt-icon.ico"),
    _volumeLabel(new QLabel(this)),
    _volumeSlider(new QSlider(Qt::Horizontal, this)),
    _fileMetadata(new QLabel(this)),
    _players(new QVector<QMediaPlayer *>),
    _currentPlayer(new QMediaPlayer),
    _defaultMusicDirectory(new QString(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory))),
    _progressBar(new QProgressBar(this)),
    _shuffleButton(new QPushButton),
    _playlistViews(new QVector<QListWidget *>),
    _currentPlaylistView(new QListWidget),
    _playlistTabs(new QTabWidget(this)),
    _newPlaylistTabButton(new QPushButton("New Playlist")),
    _loopCheckbox(new QCheckBox(this))
{
    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");
    setCentralWidget(_centralWidget);

    /****************SETTING UP STATUS BAR*********************/
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#ifndef __ANDROID__
    _infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));

    _infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    _infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(_infoLabel);
    layout->addWidget(bottomFiller);

    /************SETTING UP STATUS BAR********************/


    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    _currentPlayer->setVolume(50);

    setup();
}

QStringList * MainWindow::getAllMusicFiles(const QString& searchDirectory)
{
    QDir dir(searchDirectory);
    QFileInfoList list = dir.entryInfoList();
    QStringList * audioFiles = new QStringList;

    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];

        QString sFilePath = info.filePath();
        if (info.isDir())
        {
            // recursive
            if (info.fileName()!=".." && info.fileName()!=".")
            {
                audioFiles->append(*getAllMusicFiles(sFilePath));
            }
        }
        else
        {
            QString suff = info.suffix().toLower();
            if(suff == "mp3" || suff == "flac" || suff == "mp4" || suff == "m4a")
                audioFiles->append(info.absoluteFilePath());
        }
    }

    return audioFiles;
}

MainWindow::~MainWindow()
{
    delete _ui;
}
