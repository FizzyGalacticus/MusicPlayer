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
    void playButtonIsPressed ()
    {
        //playButton.setHidden(isPressed);
        playButton.setText("Play");
    }
private:
    Ui::MainWindow *ui;
    QPushButton playButton, playButton2;
    QIcon playButtonIcon;
};

#endif // MAINWINDOW_H
