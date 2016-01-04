/**
 *  @file
 *  @brief The file contains the Square class
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

#ifndef SQUARE_H
#define SQUARE_H

#include <QtGui>

namespace Ui {
    class Square;
}

class Square
{
  private:
        int step;
        int height;
        int width;
        bool directionX;
        bool directionY;
        bool sound;
        int xOffset;
        int yOffset;
        QGraphicsPixmapItem *image;

  public:
        // Constructor & Destructor
        Square();
        ~Square();

        // Other
        void draw(void);
        void move(void);
        bool collision(Square *red);

        // Setters
        void setX(int x);
        void setY(int y);
        void setOffsetX(int x);
        void setOffsetY(int y);
        void setStep(int step1);
        void setDirectionX(bool direction1);
        void setDirectionY(bool direction1);
        void setImage(QString image);
        void setSound(bool sound1);

        // Getters
        int getX(void);
        int getY(void);
        int getStep(void);
        int getWidth(void);
        int getHeight(void);

        QGraphicsPixmapItem *getImage();
};

#endif // SQUARE_H
