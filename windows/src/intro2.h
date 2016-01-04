/**
 *  @file
 *  @brief The file contain the Intro2 window
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

#ifndef INTRO2_H
#define INTRO2_H

#include <QWidget>
#include <QtGui>

#include "intro3.h"

namespace Ui {
    class Intro2;
}

class Intro2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Intro2(QWidget *parent = 0);
    ~Intro2();

public Q_SLOTS:
     void stateMachine();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::Intro2 *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *logo;
    float scale;
    QTimer *timer;

    Intro3 *intro3;
};

#endif // INTRO2_H
