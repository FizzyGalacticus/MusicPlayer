#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QSlider>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QStringList>
#include <QList>
#include <QStyle>
#include <QProgressBar>
#include <QCheckBox>
#include <QListView>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QMediaPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetupShuffleCheckbox();
protected:
        void rightClickMenu(QContextMenuEvent *event);

private slots:
    /***********BUTTON SLOTS***********/
    void _playButtonIsPressed ();

    void _nextButtonIsPressed ();

    void _prevButtonIsPressed ();

    /***********VOLUME SLIDER SLOT***********/
    void _volumeSliderValueChanged();

    /**************MENU OPTION SLOTS****************/
    void open();
    void play();
    void nextSong();
    void previousSong();
    void about();
    void aboutQt();
    void aboutAuthors();

    /*************Media Player Slots************/
    void playbackPositionChanged(qint64 position);
    void durationHasChanged(qint64 duration);

    /*************SHUFFLE CHECKBOX SLOT*********/
    void shuffleCheckboxHasChanged(int state);

private:
    Ui::MainWindow *_ui;
    QIcon _mainWindowIcon;
    bool _isPlaying;
    bool _isShuffled;

    /************Prev Button Objects*************/
    QPushButton *_prevButton;
    QIcon _prevButtonIcon;

    /************Play Button Objects*************/
    QPushButton *_playButton;
    QIcon _playButtonPlayIcon, _playButtonPauseIcon;

    /************Next Button Objects*************/
    QPushButton *_nextButton;
    QIcon _nextButtonIcon;

    /**************Menu Objects and Functions***/
    void createActions();
    void createMenus();

    QMenu *_fileMenu;
    QMenu *_playMenu;
    QMenu *_helpMenu;
    QAction *_openAct;
    QAction *_playAct;
    QAction *_nextSongAct;
    QAction *_previousSongAct;
    QAction *_exitAct;
    QAction *_aboutAct;
    QAction *_aboutQtAct;
    QAction *_aboutAuthorsAct;
    QLabel *_infoLabel;

    QIcon _helpIcon, _infoIcon, _openIcon, _exitIcon, _qtIcon;

    /************Volume Slider*******************/
    QLabel *_volumeLabel;
    QSlider *_volumeSlider;

    /************File Name Display**************/
    QLabel * _fileMetadata;

    /***********Media Player*********************/
    QMediaPlayer * _player;
    QMediaPlaylist * _playlist;

    /**************Progress bar*****************/
    QProgressBar * _progressBar;

    /**************Shuffle Checkox**************/
    QCheckBox *_shuffleCheckbox;
    QLabel *_shuffleCheckboxLabel;

    /**************Playlist View***************/
    QListView *_playlistView;

    /*************SETUP FUNCTIONS***************/
    void setupButtons();
    void setupProgressBar();
    void setupVolumeLabelAndSlider();
    void setupMetadataLabel();
    void setupShuffleCheckbox();
    void setupMenus();
    void setup();
};

#endif // MAINWINDOW_H
