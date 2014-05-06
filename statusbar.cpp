#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QtWidgets>

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

/****************SETTING UP MENUS*********************/
createActions();
createMenus();

/************SETTING UP STATUS BAR********************/
#ifndef Q_OS_SYMBIAN
QString message = tr("A context menu is available by right-clicking");
statusBar()->showMessage(message);
#endif

_player->setVolume(50);

setupButtons();
setupProgressBar();
setupVolumeLabelAndSlider();
setupShuffleCheckbox();
setupMetadataLabel();
