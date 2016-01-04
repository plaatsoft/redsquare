/**
 *  @file
 *  @brief The file contain the score window
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

#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include <QtGui>

#include "HighScore.h"

namespace Ui {
    class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = 0);
    ~Score();
    void setHighScore(HighScore *highscore1);

private:
    // private variables
    Ui::Score *ui;
    QGraphicsScene *scene;
    HighScore *highscore;

    // private methods
    const char * getDate(time_t *date);
    void FillTable(void);

private slots:
    void on_backButton_clicked();
};

#endif // SCORE_H
