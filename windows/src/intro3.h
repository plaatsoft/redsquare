/**
 *  @file
 *  @brief The file contain the Intro3 window
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

#ifndef INTRO3_H
#define INTRO3_H

#include <QWidget>
#include <QtGui>

#include "mainmenu.h"

namespace Ui {
    class Intro3;
}

class Intro3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Intro3(QWidget *parent = 0);
    ~Intro3();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::Intro3 *ui;
    QGraphicsScene *scene;

    MainMenu *mainMenu;
};

#endif // INTRO3_H
