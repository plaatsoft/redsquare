/**
 *  @file
 *  @brief The file contain the menu window
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

#include <QGraphicsScene>

#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "General.h"

// ------------------------------
// Constructor & Destructor
// ------------------------------

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainMenu)
{        
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);

    // Init blue squares
    initSquares();
    scene->addItem(blue1->getImage());
    scene->addItem(blue2->getImage());
    scene->addItem(blue3->getImage());
    scene->addItem(blue4->getImage());

    // Timer for animation
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveSquares()));
    timer->start(15);

    // Set Windows Title
    char tmp[100];
    sprintf(tmp,"<html><body style=color:#ffffff;>%s v%s</body></html>", APPL_NAME, APPL_VERSION);
    ui->ApplLabel->setText(tmp);

    sprintf(tmp,"<html><body style=color:#ffffff;>%s</body></html>", APPL_DATE);
    ui->dateLabel->setText(tmp);

    // Load highscore
    highscore = new HighScore();
    highscore->load();
    highscore->save();

    // Initi Netwokr layer
    initNetwork();
}

MainMenu::~MainMenu()
{
    delete ui;
}

// ------------------------------
// Other
// ------------------------------

void MainMenu::initSquares() {

    // Blue Square 1
    blue1 = new Square();
    blue1->setImage(":/images/bluesquare1.png");
    blue1->setX(10);
    blue1->setY(10);
    blue1->setStep(1);
    blue1->setSound(false);
    blue1->setDirectionX(true);
    blue1->setDirectionY(true);

    // Blue Square 2
    blue2 = new Square();
    blue2->setImage(":/images/bluesquare2.png");
    blue2->setX(510);
    blue2->setY(10);
    blue2->setStep(1);
    blue2->setSound(false);
    blue2->setDirectionX(false);
    blue2->setDirectionY(true);

    // Blue Square 3
    blue3 = new Square();
    blue3->setImage(":/images/bluesquare3.png");
    blue3->setX(10);
    blue3->setY(355);
    blue3->setStep(1);
    blue3->setSound(false);
    blue3->setDirectionX(true);
    blue3->setDirectionY(false);

    // Blue Square 4
    blue4 = new Square();
    blue4->setImage(":/images/bluesquare4.png");
    blue4->setX(570);
    blue4->setY(410);
    blue4->setStep(1);
    blue4->setSound(false);
    blue4->setDirectionX(false);
    blue4->setDirectionY(false);
}

void MainMenu::moveSquares() {

   blue1->move();
   blue2->move();
   blue3->move();
   blue4->move();
}

// ------------------------------
// Network
// ------------------------------

/**
 * Start network
 */
void MainMenu::initNetwork(void)
{
   manager = new QNetworkAccessManager(this);

   connect( manager,
         SIGNAL(finished(QNetworkReply*)),
         this,
         SLOT(replyFinished(QNetworkReply*)) );

   fetchVersion();
}

/**
 * Process incoming http response
 */
void MainMenu::replyFinished(QNetworkReply *reply)
{
    QString bytesCount = QString::number( reply->bytesAvailable());
    QString result = reply->readAll();

    qDebug() << bytesCount << "Bytes received ";

    qDebug() << result;

    switch (stateMachine)
    {
        case STATE_VERSION_CHECK:
        {
            parseVersion(result);
            fetchReleaseNotes();
        }
        break;

        case STATE_RELEASE_NOTES:
        {
            parseReleaseNotes(result);
            stateMachine=STATE_IDLE;
        }
        break;
    }
}

/**
 * Create http request for version data.
 */
void MainMenu::fetchVersion()
{
    qDebug() << "fetchVersion enter";

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.plaatsoft.nl/service/redsquare.html"));

    manager->get(request);
    stateMachine=STATE_VERSION_CHECK;

    qDebug() << "fetchVersion leave ";
}

/**
 * Create http request for release notes data.
 */
void MainMenu::fetchReleaseNotes()
{
    qDebug() << "fetchReleaseNotes enter";

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.plaatsoft.nl/service/redsquare.html"));

    manager->get(request);
    stateMachine=STATE_RELEASE_NOTES;

    qDebug() << "fetchReleaseNotes leave";
}

/**
 * Parse data for version information
 */
void MainMenu::parseVersion(QString response)
{
   qDebug() << response;

   QString text;
   int pos = response.indexOf("Version ");
   QString version = response.mid(pos+8,4).simplified();
   qDebug() << "Version = [" << version << "]";

   if (version.size()>0) {

       if (version.compare(APPL_VERSION)!=0) {

            text="<html><body style=color:#ffffff;>Version ";
            text+=version;
            text+=" is available!<br>";
            text+="Check the release notes for more information.</body></html>";
        } else {
           text="<html><body style=color:#ffffff;>No update available!</body></html>";
        }
        ui->newversionLabel->setText(text);

   } else {
       text = "<html><body style=color:#ffffff;>New version check failed!</body></html>";
       ui->newversionLabel->setText(text);
   }
}

/**
 * Parse data for version information
 */
void MainMenu::parseReleaseNotes(QString response)
{
   qDebug() << response;

   // Store release notes
   notes=response;
}

// ------------------------------
// User Actions
// ------------------------------

void MainMenu::on_playButton_clicked()
{
    gameboard = new GameBoard();
    gameboard->setHighScore(highscore);
    setCentralWidget(gameboard);
}

void MainMenu::on_creditsButton_clicked()
{
    credits = new Credits();
    setCentralWidget(credits);
}

void MainMenu::on_helpButton_clicked()
{
    help = new Help();
    setCentralWidget(help);
}

void MainMenu::on_donateButton_clicked()
{
    donate = new Donate();
    setCentralWidget(donate);
}

void MainMenu::on_scoreButton_clicked()
{
    score = new Score();
    score->setHighScore(highscore);
    setCentralWidget(score);
}

void MainMenu::on_releasenotesButton_clicked()
{
   releasenotes = new ReleaseNotes();
   releasenotes->setNotes(notes);
   setCentralWidget(releasenotes);
}

void MainMenu::on_exitButton_clicked()
{
    exit(0);
}

// ------------------------------
// The end
// ------------------------------




