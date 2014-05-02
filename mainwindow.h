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
    /***********PLAY BUTTON FUNCTION SLOTS***********/
    void playButtonIsPressed ()
    {
        if(!isPlaying) playButton.setIcon(playButtonPlayIcon);
        else playButton.setIcon(playButtonPauseIcon);

        isPlaying = !isPlaying;
    }
private:
    Ui::MainWindow *ui;

    /************Play Button Objects*************/
    QPushButton playButton, playButton2;
    QIcon playButtonPlayIcon, playButtonPauseIcon;
    bool isPlaying;
};

#endif // MAINWINDOW_H
