/**
 *  @file
 *  @brief The file contain the Intro1 window
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

#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include <QtGui>

#include "intro2.h"

namespace Ui {
    class Intro;
}

class Intro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = 0);
    ~Intro();

public Q_SLOTS:
    void stateMachine();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::Intro *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *logo;
    float scale;
    QTimer *timer;

    Intro2 *intro2;

    void closeEvent(QCloseEvent *event);
    void readSettings();
    void writeSettings();
 };

#endif // INTRO_H
