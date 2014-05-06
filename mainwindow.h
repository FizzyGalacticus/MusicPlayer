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

protected:
        void contextMenuEvent(QContextMenuEvent *event);

private slots:
    /***********BUTTON SLOTS***********/
    void playButtonIsPressed ();

    void nextButtonIsPressed ();

    void prevButtonIsPressed ();

    /***********VOLUME SLIDER SLOT***********/
    void volumeSliderValueChanged();

    /**************MENU OPTION SLOTS****************/
    void open();
    void play();
    void nextSong();
    void previousSong();
    void about();
    void aboutQt();

private:
    Ui::MainWindow *ui;
    QIcon mainWindowIcon;
    bool isPlaying;

    /************Prev Button Objects*************/
    QPushButton prevButton;
    QIcon prevButtonIcon;

    /************Play Button Objects*************/
    QPushButton playButton;
    QIcon playButtonPlayIcon, playButtonPauseIcon;

    /************Next Button Objects*************/
    QPushButton nextButton;
    QIcon nextButtonIcon;

    /**************Menu Objects and Functions***/
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *playMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *playAct;
    QAction *nextSongAct;
    QAction *previousSongAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

    /************Volume Slider*******************/
    QLabel *volumeLabel;
    QSlider *volumeSlider;

    /************File Name Display**************/
    QLabel * _filename;

    /***********Media Player*********************/
    QMediaPlayer * _player;
    QMediaPlaylist * _playlist;

    /*************SETUP FUNCTIONS***************/
    void setupButtons();
};

#endif // MAINWINDOW_H
