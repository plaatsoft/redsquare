/**
 *  @file
 *  @brief The file contain the  gameboard window
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

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <time.h>
#include <QtGui>

#include "Square.h"
#include "HighScore.h"

namespace Ui {
    class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

    void setHighScore(HighScore *highscore1);

public Q_SLOTS:
    void statemachine();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::GameBoard *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *border;
    QCursor *cursor;
    QMouseEvent *mouse;
    QLabel *text;
    QTimer *timer;
    HighScore *highscore;

    Square *blue1;
    Square *blue2;
    Square *blue3;
    Square *blue4;
    Square *red;

    time_t startTime;
    int score;
    int step;
    bool stop;
    bool redActive;

    void initGame();
    void moveRedSquare();
    bool collision();

private slots:
    void on_backButton_clicked();
};

#endif // GAMEBOARD_H
