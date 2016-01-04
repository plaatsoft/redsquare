/**
 *  @file
 *  @brief The file contains the Square class methods
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

#include "General.h"
#include "Square.h"

#include <QSound>

// ------------------------------
// Constructor & DeSctructor
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
Square::Square()
{
    height=0;
    width=0;
    step=0;
    directionX=true;
    directionY=true;
    xOffset=0;
    yOffset=0;
}

/**
 * Destructor
 * Clean up all allocated memory
 */
Square::~Square()
{

}

// ------------------------------
// Other
// ------------------------------

void Square::move(void)
{
    QPointF pos = image->pos();

    if (directionX){
        if ( pos.rx()<(SCREEN_WIDTH-width)) {
            pos.rx()+=step;
        } else {
            if (sound) QSound::play("snd/border.wav");
            directionX=false;
        }
    } else {
        if ( pos.rx()>0) {
            pos.rx()-=step;
        } else {
            if (sound) QSound::play("snd/border.wav");
            directionX=true;
        }
    }

    if (directionY){
        if ( pos.ry()<(SCREEN_HEIGHT-height)) {
            pos.ry()+=step;
        } else {
           if (sound) QSound::play("snd/border.wav");
           directionY=false;
        }
    } else {
        if ( pos.ry()>0) {
            pos.ry()-=step;
        } else {
           if (sound) QSound::play("snd/border.wav");
           directionY=true;
        }
    }
    image->setPos(pos);
}

bool Square::collision(Square *red)
{
    bool collision=false;
    int x = image->pos().rx();
    int y = image->pos().ry();

    if ((red->getX()>=x) && (red->getX()<=x+width))
    {
       if ((red->getY()>=y) && (red->getY()<=y+height))
       {
            collision = true;
       }
    }

    if ((red->getX()+red->getWidth()>=x) && (red->getX()+red->getWidth()<=x+width))
    {
       if ((red->getY()>=y) && (red->getY()<=y+height))
       {
            collision = true;
       }
    }

    if ((red->getX()>=x) && (red->getX()<=x+width))
    {
       if ((red->getY()+red->getHeight()>=y) && (red->getY()+red->getHeight()<=y+height))
       {
            collision = true;
       }
    }

    if ((red->getX()+red->getWidth()>=x) && (red->getX()+red->getWidth()<=x+width))
    {
       if ((red->getY()+red->getHeight()>=y) && (red->getY()+red->getHeight()<=y+height))
       {
            collision = true;
       }
    }
    return collision;
}

// ------------------------------
// Getters
// ------------------------------

/**
 * Get x postion.
 * @return x    The current X position of the square.
 */
int Square::getX(void)
{
    return image->pos().rx();
}

/**
 * Get y postion.
 * @return y    The current Y position of the square.
 */
int Square::getY(void)
{
    return image->pos().ry();
}

/**
 * Get step postion.
 * @return step    The current step size of the square.
 */
int Square::getStep(void)
{
    return step;
}

/**
 * Get square height.
 * @return heigth    The the height of the square.
 */
int Square::getHeight(void)
{
    return height;
}


/**
 * Get square width.
 * @return width    The the width of the square.
 */
int Square::getWidth(void)
{
    return width;
}

/**
 * Get image.
 * @return image    Get the current image of the square.
 */
QGraphicsPixmapItem *Square::getImage(void)
{
    return image;
}

// ------------------------------
// Setters
// ------------------------------

/**
 * Set square image.
 * @param filename  The filename of the bitmap.
 */
void Square::setImage(QString filename)
{
    image= new QGraphicsPixmapItem(QPixmap(filename));
    height= image->boundingRect().height();
    width= image->boundingRect().width();
}

/**
 * Set x postion.
 * @param x     The X position of the square.
 */
void Square::setX(int x)
{   
    QPointF pos = image->pos();
    pos.rx()=x+xOffset;
    image->setPos(pos);
}

/**
 * Set y postion.
 * @param y    The Y position of the square.
 */
void Square::setY(int y)
{
    QPointF pos = image->pos();
    pos.ry()=y+yOffset;
    image->setPos(pos);
}

void Square::setOffsetX(int x)
{
   xOffset=x;
}

void Square::setOffsetY(int y)
{
   yOffset=y;
}

/**
 * Set step postion.
 * @param step1     The step size of the square.
 */
void Square::setStep(int step1)
{
    step = step1;
}

/**
 * Set x direction.
 * @param direction1    The X direction of the square.
 */
void Square::setDirectionX(bool direction1)
{
    directionX = direction1;
}

/**
 * Set y direction.
 * @param direction1    The Y direction of the square.
 */
void Square::setDirectionY(bool direction1)
{
    directionY = direction1;
}

/**
 * Set sound on/off.
 * @param sound1    The sound off or on.
 */
void Square::setSound(bool sound1)
{
    sound = sound1;
}

// ------------------------------
// The end
// ------------------------------
