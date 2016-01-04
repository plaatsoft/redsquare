/**
 *  @file
 *  @brief The file contain the main window
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

#include <QSound>

#include "General.h"
#include "Square.h"
#include "gameboard.h"
#include "ui_gameboard.h"

// ------------------------------
// Constructor & DeSctructor
// ------------------------------

GameBoard::GameBoard(QWidget *parent) :  QWidget(parent),  ui(new Ui::GameBoard)
{
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background.png"));

     QSound::play("snd/start.wav");

    // Init Game parameters
    initGame();

    // Add white border
    scene->addItem(border);

    // Add squares to gameboard
    scene->addItem(blue1->getImage());
    scene->addItem(blue2->getImage());
    scene->addItem(blue3->getImage());
    scene->addItem(blue4->getImage());
    scene->addItem(red->getImage());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);

    // Init statemachine
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(statemachine()));
    timer->start(15);
}

GameBoard::~GameBoard()
{
    delete ui;
}

// ------------------------------
// User actions
// ------------------------------

void GameBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

       QPointF pos = mapFromGlobal(cursor->pos());

       if ( pos.x()>red->getX() &&
            pos.x()<red->getX()+red->getWidth() &&
            pos.y()>red->getY() &&
            pos.y()<red->getY()+red->getHeight() ) {

          red->setOffsetX(red->getX()-pos.x());
          red->setOffsetY(red->getY()-pos.y());
          redActive = true;
       }
    }
}

void GameBoard::mouseMoveEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton) {
       redActive = true;
   }
}

void GameBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && redActive) {
        redActive = false;
    }
}

void GameBoard::on_backButton_clicked()
{
    timer->stop();
    close();
}

// ------------------------------
// Getters & Setters
// ------------------------------

void GameBoard::setHighScore(HighScore *highscore1)
{
     highscore=highscore1;
}

// ------------------------------
// Other
// ------------------------------

void GameBoard::initGame() {

    score=0;
    step=1;
    stop=false;
    redActive=false;

    startTime = time(NULL);

    ui->scoreText->setText("");
    ui->scoreValue1->setText("");
    ui->scoreValue2->setText("");
    ui->gameOverText->setText("");
    ui->highScoreText->setText("");
    ui->timeValueText->setText("");
    ui->playTimeText->setText("");
    ui->playTimeValue->setText("");
    ui->backButton->setVisible(false);

    // Blue Square 1
    blue1 = new Square();
    blue1->setImage(":/images/bluesquare1.png");
    blue1->setX(10);
    blue1->setY(10);
    blue1->setSound(true);
    blue1->setStep(step);
    blue1->setDirectionX(true);
    blue1->setDirectionY(true);

    // Blue Square 2
    blue2 = new Square();
    blue2->setImage(":/images/bluesquare2.png");
    blue2->setX(510);
    blue2->setY(10);
    blue2->setSound(true);
    blue2->setStep(step);
    blue2->setDirectionX(false);
    blue2->setDirectionY(true);

    // Blue Square 3
    blue3 = new Square();
    blue3->setImage(":/images/bluesquare3.png");
    blue3->setX(10);
    blue3->setY(355);
    blue3->setSound(true);
    blue3->setStep(step);
    blue3->setDirectionX(true);
    blue3->setDirectionY(false);

    // Blue Square 4
    blue4 = new Square();
    blue4->setImage(":/images/bluesquare4.png");
    blue4->setX(570);
    blue4->setY(410);
    blue4->setSound(true);
    blue4->setStep(step);
    blue4->setDirectionX(false);
    blue4->setDirectionY(false);

    // Red Square
    red = new Square();
    red->setImage(":/images/redsquare.png");
    red->setX(280);
    red->setY(200);

    border = new QGraphicsRectItem();
    border->setPen(QPen());
    border->setRect( BORDER_SIZE, BORDER_SIZE, SCREEN_WIDTH-(BORDER_SIZE*2), SCREEN_HEIGHT-(BORDER_SIZE*2) );
    border->setBrush( QBrush((QColor(255,255,255,150)), Qt::SolidPattern));
}

bool GameBoard::collision()
{
    bool coll = false;

    // Detect collision with wall.
    if (red->getX()<BORDER_SIZE) {
       coll = true;
    }

    if ((red->getX()+red->getWidth())>(SCREEN_WIDTH-BORDER_SIZE+2)) {
       coll = true;
    }

    if (red->getY()<BORDER_SIZE) {
       coll = true;
    }

    if ((red->getY()+red->getHeight())>(SCREEN_HEIGHT-BORDER_SIZE+2)) {
       coll = true;
    }

    // Detect collision with blue square.
    if (!coll) {
        coll=blue1->collision(red);
    }

    if (!coll) {
        coll=blue2->collision(red);
    }

    if (!coll) {
        coll=blue3->collision(red);
    }

    if (!coll) {
        coll=blue4->collision(red);
    }

    return coll;
}

void GameBoard::moveRedSquare() {

    QPointF pos = mapFromGlobal(cursor->pos());

    red->setX(pos.x());
    red->setY(pos.y());
}

void GameBoard::statemachine() {

   char tmp[100];
   struct tm *level;

   // Move all blue squares
   if (stop) return;

   blue1->move();
   blue2->move();
   blue3->move();
   blue4->move();

   // Move red square
   if (redActive) {
       moveRedSquare();
   }

   // Update score
   score++;
   sprintf(tmp,"<html><body style=color:#ffffff;font-size:12pt;>%0d</body></html>",score);
   ui->scoreValue1->setText(tmp);

   // Show play time
   time_t playTime = time(NULL)-startTime;
   level = localtime(&playTime);
   sprintf(tmp,"<html><body style=color:#ffffff;font-size:12pt;>%02d:%02d:%02d</body></html>",level->tm_hour-1, level->tm_min, level->tm_sec);
   ui->timeValueText->setText(tmp);

   // Every +/- 10 seconds increase the blue sqaure speed
   if ((score % 650)==0) {
       step++;
       blue1->setStep(step);
       blue2->setStep(step);
       blue3->setStep(step);
       blue4->setStep(step);
   }

   // Check if collision has occures
   if (collision()) {
        stop=true;
        ui->gameOverText->setText("GAME OVER");
        ui->scoreText->setText("Score");

        ui->playTimeText->setText("Play Time");
        sprintf(tmp,"<html><body style=color:#000000;>%02d:%02d:%02d</body></html>",level->tm_hour-1, level->tm_min, level->tm_sec);
        ui->playTimeValue->setText(tmp);

        sprintf(tmp,"<html><body style=color:#000000;>%04d</body></html>",score);
        ui->scoreValue2->setText(tmp);
        ui->backButton->setVisible(true);
        QSound::play("snd/gameover.wav");

        QSettings settings("PlaatSoft", APPL_NAME);
        QString name=settings.value("username", "Player 1").toString();
        int range = highscore->setScore(name,step,score);
        highscore->save();

        if (range>0) {
          sprintf(tmp,"Player 1 win, %dth place in highscore!",range+1);
          ui->highScoreText->setText(tmp);
        }
   }
}

// ------------------------------
// The end
// ------------------------------
