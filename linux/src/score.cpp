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

#include "score.h"
#include "ui_score.h"

// ------------------------------
// Constructor & Destructor
// ------------------------------

Score::Score(QWidget *parent) : QWidget(parent), ui(new Ui::Score)
{
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);
}

Score::~Score()
{
    delete ui;
}

// ------------------------------
// User Actions
// ------------------------------

void Score::on_backButton_clicked()
{
   close();
}

// ------------------------------
// Getters & Setters
// ------------------------------


void Score::setHighScore(HighScore *highscore1)
{
     highscore=highscore1;
     FillTable();
     ui->tableWidget->setStyleSheet("QTableWidget { background:transparent;color:#ffffff; }");
}

// ------------------------------
// Other
// ------------------------------

/**
 * Convert date to String
 */
const char *Score::getDate(time_t *date)
{
  struct tm *now = NULL;
  static char buf[ 50 ] ;

  /* Get time and date structure */
  now = localtime(date);

  // Create time stamp
  sprintf(buf,"%02d-%02d-%04d %02d:%02d:%02d",
        now->tm_mday, now->tm_mon+1, now->tm_year+1900,
        now->tm_hour,now->tm_min,now->tm_sec);

  return buf;
}

/**
 * Fill table with data
 */
void Score::FillTable(void)
{
    QTableWidgetItem *item;

   // Set table dimensions
   ui->tableWidget->setColumnCount(5);
   ui->tableWidget->setColumnWidth(0,50);
   ui->tableWidget->setColumnWidth(1,200);
   ui->tableWidget->setColumnWidth(2,75);
   ui->tableWidget->setColumnWidth(3,75);
   ui->tableWidget->setColumnWidth(4,150);

   //qDebug() << highscore->getAmount()+1;
   ui->tableWidget->setRowCount(highscore->getAmount());

   // Create Table Data
   for (int y=0; y<highscore->getAmount(); y++)
   {
      item = new QTableWidgetItem(QString::number(y+1));
      ui->tableWidget->setItem(y, 0, item);

      item = new QTableWidgetItem(getDate(highscore->getDate(y)));
      ui->tableWidget->setItem(y, 1, item);

      item = new QTableWidgetItem(QString::number(highscore->getScore(y)));
      ui->tableWidget->setItem(y, 2, item);

      item = new QTableWidgetItem(QString::number(highscore->getLevel(y)));
      ui->tableWidget->setItem(y, 3, item);

      item = new QTableWidgetItem(highscore->getName(y));
      ui->tableWidget->setItem(y, 4, item);
   }
}

// ------------------------------
// The End
// ------------------------------
