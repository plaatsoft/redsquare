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

#include "intro2.h"
#include "ui_intro2.h"

#include "General.h"

// ------------------------------
// Constructor & Destructor
// ------------------------------

Intro2::Intro2(QWidget *parent): QMainWindow(parent), ui(new Ui::Intro2)
{
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background2.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);

    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo2.png"));
    logo->setPos(300,240);
    logo->scale(0.1,0.1);
    scene->addItem(logo);

    scale=0.1;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(stateMachine()));
    timer->start(15);
}

Intro2::~Intro2()
{
    delete ui;
}

// ------------------------------
// User actions
// ------------------------------

void Intro2::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
       intro3 = new Intro3();
       setCentralWidget(intro3);
       timer->stop();
     }
}

// ------------------------------
// Other
// ------------------------------

void Intro2::stateMachine(void) {

    if (scale<60) {
        scale++;

        // Workarround to centre the image before scale it!
        logo->setTransform(QTransform().
            translate(logo->boundingRect().width()/2, logo->boundingRect().height()/2).
            scale(1.04,1.04).
            translate(-(logo->boundingRect().width()/2), -(logo->boundingRect().height()/2)), true);
    }
}

// ------------------------------
// The end
// ------------------------------
