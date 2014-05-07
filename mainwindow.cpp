#include "actions.h"
#include "componentactions.h"
#include "menus.h"
#include "menuactions.h"
#include "setup.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _mainWindowIcon(":/Resources/icons/mainWindowIcon.png"),
    _isPlaying(false),
    _isShuffled(false),
    _prevButton(new QPushButton(this)),
    _playButton(new QPushButton(this)),
    _nextButton(new QPushButton(this)),
    _prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    _playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    _playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    _nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    _helpIcon(":/Resources/icons/Menu-Help-icon.png"),
    _infoIcon(":/Resources/icons/Menu-Info-icon.png"),
    _openIcon(":/Resources/icons/Menu-Open-icon.png"),
    _exitIcon(":/Resources/icons/Menu-Exit-icon.png"),
    _qtIcon(":/Resources/icons/Qt-icon.ico"),
    _volumeLabel(new QLabel(this)),
    _volumeSlider(new QSlider(Qt::Horizontal, this)),
    _fileMetadata(new QLabel(this)),
    _player(new QMediaPlayer(this)),
    _playlist(new QMediaPlaylist(this)),
    _progressBar(new QProgressBar(this)),
    _shuffleCheckbox(new QCheckBox("Shuffle", this)),
    _playlistView(new QListView(this))
{
    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");

    setFixedWidth(7*72);
    setFixedHeight(7*72);

    /****************SETTING UP STATUS BAR*********************/
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#ifdef Q_OS_SYMBIAN
    _infoLabel = new QLabel(tr("<i>Choose a menu option</i>"));
#else
    _infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
#endif
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

    #ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
    #endif

    _player->setVolume(50);

    setup();

}

MainWindow::~MainWindow()
{
    delete _ui;
}
