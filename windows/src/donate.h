/**
 *  @file
 *  @brief The file contain the Donate window
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

#ifndef DONATE_H
#define DONATE_H

#include <QWidget>
#include <QtGui>

namespace Ui {
    class Donate;
}

class Donate : public QWidget
{
    Q_OBJECT

public:
    explicit Donate(QWidget *parent = 0);
    ~Donate();

private:
    Ui::Donate *ui;
    QGraphicsScene *scene;

private slots:
    void on_backButton_clicked();
};

#endif // DONATE_H
