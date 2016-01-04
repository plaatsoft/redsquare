/**
 *  @file
 *  @brief The file contain the ReleaseNotes window
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

#ifndef RELEASENOTES_H
#define RELEASENOTES_H

#include <QWidget>
#include <QtGui>

namespace Ui {
    class ReleaseNotes;
}

class ReleaseNotes : public QWidget
{
    Q_OBJECT

public:
    explicit ReleaseNotes(QWidget *parent = 0);
    ~ReleaseNotes();

    void setNotes(QString text);

private:
    Ui::ReleaseNotes *ui;
    QGraphicsScene *scene;

private slots:
    void on_backButton_clicked();
};

#endif // RELEASENOTES_H
