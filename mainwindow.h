#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /***********PLAY BUTTON FUNCTION SLOT***********/
    void playButtonIsPressed ()
    {
        if(!isPlaying) playButton.setIcon(playButtonPauseIcon);
        else playButton.setIcon(playButtonPlayIcon);

        isPlaying = !isPlaying;
    }

    /***********NEXT BUTTON FUNCTION SLOT***********/
    void nextButtonIsPressed ()
    {
        //Go to next song
    }

    /***********PREV BUTTON FUNCTION SLOT***********/
    void prevButtonIsPressed ()
    {
        //Go to previous song
    }
private:
    Ui::MainWindow *ui;
    QIcon mainWindowIcon;

    /************Play Button Objects*************/
    QPushButton playButton;
    QIcon playButtonPlayIcon, playButtonPauseIcon;
    bool isPlaying;

    /************Next Button Objects*************/
    QPushButton nextButton;
    QIcon nextButtonIcon;

    /************Prev Button Objects*************/
    QPushButton prevButton;
    QIcon prevButtonIcon;
};

#endif // MAINWINDOW_H
