/**
 *  @file
 *  @brief The file contain the help window
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

#include "help.h"
#include "ui_help.h"
#include "General.h"

// ------------------------------
// Constructor & DeSctructor
// ------------------------------

Help::Help(QWidget *parent) : QWidget(parent), ui(new Ui::help)
{
    ui->setupUi(this);

    // Add background screen
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0,SCREEN_WIDTH+2,SCREEN_HEIGHT+2);
}

Help::~Help()
{
    delete ui;
}

// ------------------------------
// User Action
// ------------------------------

void Help::on_backButton_clicked()
{
    close();
}

// ------------------------------
// The end
// ------------------------------
