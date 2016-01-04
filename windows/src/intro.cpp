/**
 *  @file
 *  @brief The file contain the intro window
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

#include "intro.h"
#include "ui_intro.h"
#include "General.h"

// ------------------------------
// Constructor & Destructor
// ------------------------------

Intro::Intro(QWidget *parent) : QMainWindow(parent), ui(new Ui::Intro)
{
    ui->setupUi(this);

    // Init grab mouse events
    //grabMouse();

    readSettings();

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);

    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));
    logo->setPos(300,240);
    logo->scale(0.1,0.1);
    scene->addItem(logo);

    // Set fix windows form size.
    setMinimumSize(SCREEN_WIDTH+2,SCREEN_HEIGHT+2);
    setMaximumSize(SCREEN_WIDTH+2,SCREEN_HEIGHT+2);

    // Set Windows Title
    char tmp[100];
    sprintf(tmp,"%s v%s", APPL_NAME, APPL_VERSION);
    setWindowTitle(tmp);

    scale=0.1;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(stateMachine()));
    timer->start(15);
}

Intro::~Intro()
{
    delete ui;
}

// ------------------------------
// User actions
// ------------------------------

/**
 * Close Window
 */
void Intro::closeEvent(QCloseEvent *event)
{
   // Store current window position
   writeSettings();
}

void Intro::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        intro2 = new Intro2();
        setCentralWidget(intro2);
        timer->stop();
     }
}

// ------------------------------
// Other
// ------------------------------

void Intro::stateMachine(void) {

    if (scale<60) {
        scale++;

        // Workarround to centre the image before scale it!
        logo->setTransform(QTransform().
            translate(logo->boundingRect().width()/2, logo->boundingRect().height()/2).
            scale(1.04,1.04).
            translate(-(logo->boundingRect().width()/2), -(logo->boundingRect().height()/2)), true);
    }
}

/**
 * Read settings out Windows registry
 */
void Intro::readSettings()
{
    // Fetch previous window position
    QSettings settings("PlaatSoft", APPL_NAME);
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    move(pos);
    qDebug() << "pos=" << pos;
}

/**
 * Write settings to Windows registry
 */
void Intro::writeSettings()
{
    // Store current window position
    QSettings settings("PlaatSoft", APPL_NAME);
    settings.setValue("pos", pos());
    qDebug() << "pos=" << pos();
}

// ------------------------------
// The end
// ------------------------------


