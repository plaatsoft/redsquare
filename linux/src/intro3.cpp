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

#include "intro3.h"
#include "ui_intro3.h"

#include "mainmenu.h"
#include "General.h"

// ------------------------------
// Constructor & Destructor
// ------------------------------

Intro3::Intro3(QWidget *parent) : QMainWindow(parent), ui(new Ui::Intro3)
{
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background2.jpg"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);
 }

Intro3::~Intro3()
{
    delete ui;
}

// ------------------------------
// User actions
// ------------------------------

void Intro3::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mainMenu = new MainMenu();
        setCentralWidget(mainMenu);
     }
}
