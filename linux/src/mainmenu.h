/**
 *  @file
 *  @brief The file contain the MainMenu window
 *  @author wplaat
 *
 *  Copyright (C) 2008-2011 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui>
#include <QWidget>
#include <QtNetwork>

#include "HighScore.h"
#include "gameboard.h"
#include "credits.h"
#include "help.h"
#include "donate.h"
#include "score.h"
#include "releasenotes.h"

namespace Ui {
    class MainMenu;
}

enum
{
    STATE_IDLE=0,
    STATE_VERSION_CHECK=1,
    STATE_REQUEST_DATA=2,
    STATE_RELEASE_NOTES=3
};

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

public Q_SLOTS:
    void moveSquares();

protected:

private:
    // Local variables
    Ui::MainMenu *ui;
    QGraphicsScene *scene;
    HighScore *highscore;
    QTimer *timer;
    Square *blue1;
    Square *blue2;
    Square *blue3;
    Square *blue4;
    QNetworkAccessManager *manager;
    QString result;
    QString notes;

    // HTTP related variables
    int stateMachine;
    QAction *fetchAct;

    // Screens
    GameBoard *gameboard;
    Credits *credits;
    Help *help;
    Donate *donate;
    Score *score;
    ReleaseNotes *releasenotes;

    // Private methodes
    void initSquares(void);
    void initNetwork(void);
    void parseVersion(QString response);
    void parseReleaseNotes(QString response);

private slots:
    // User actions
    void on_releasenotesButton_clicked();
    void on_exitButton_clicked();
    void on_scoreButton_clicked();
    void on_donateButton_clicked();
    void on_helpButton_clicked();
    void on_creditsButton_clicked();
    void on_playButton_clicked();

    // HTTP related methods
    void fetchVersion();
    void fetchReleaseNotes();
    void replyFinished(QNetworkReply*);
};

#endif // MAINMENU_H
