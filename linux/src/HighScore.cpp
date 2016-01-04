/** 
 *  @file 
 *  @brief The file contain the HighScore class methodes
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

#include <QtGui>
#include <QtXml>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "General.h"
#include "HighScore.h"

// ------------------------------
// Constructor 
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
HighScore::HighScore()
{
	for(int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
      scores[i].localTime=0;
      scores[i].level=0;
		scores[i].score=0;
      scores[i].name="";
	}   
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
HighScore::~HighScore()
{

}

// ------------------------------
// Others
// ------------------------------

/**
 * load highscore xml file form sdcard.
 */
void HighScore::load()
{		
   maxdata=0;

   QDir::setCurrent(QDir::homePath());
   qDebug() << QDir::currentPath();
   QString fileName = "RedSquare.xml";

   QFile file(fileName);
   if (!file.open(QFile::ReadOnly)) {
      qDebug() << fileName << "not found!";
   }

   QXmlStreamReader reader(&file);

   // Parse XML data
   while (!reader.atEnd()) {
      reader.readNext();
      if (reader.isStartElement()) {
          if(reader.name() == "item") {
             scores[maxdata].score=reader.attributes().value("score").toString().toInt();
             //qDebug() << "score" << maxdata << scores[maxdata].score;

             scores[maxdata].localTime=reader.attributes().value("localTime").toString().toInt();
             //qDebug() << "localtime" << maxdata << scores[maxdata].localTime;

             scores[maxdata].level=reader.attributes().value("level").toString().toInt();
             //qDebug() << "level" << maxdata << scores[maxdata].level;

             scores[maxdata].name=reader.attributes().value("name").toString();
             //qDebug() << "name" << maxdata << scores[maxdata].name;

             maxdata++;
         }
      }
   }
}

/**
 * save highscore to xml file.
 */
void HighScore::save(void)
{	
   char tmp[MAX_LEN];

   QDir::setCurrent(QDir::homePath());
   qDebug() << QDir::currentPath();
   QString fileName = "RedSquare.xml";

   QFile file(fileName);

   if (!file.open(QFile::WriteOnly)) {
        qDebug() << fileName << "Failed to write" << file.errorString();
        return;
   }

   qDebug() << fileName << "saved!";

   QXmlStreamWriter stream(&file);
   stream.setAutoFormatting(false);
   stream.setAutoFormattingIndent(3);
   stream.writeStartDocument();

   stream.writeStartElement("highscore");

   for(int i=0; i<MAX_LOCAL_HIGHSCORE; i++) {

      stream.writeStartElement("item");

      sprintf(tmp, "%d", (int) scores[i].localTime);
      stream.writeAttribute("localTime", tmp);

	   sprintf(tmp, "%d", scores[i].score);
      stream.writeAttribute("score", tmp);

      sprintf(tmp, "%d", scores[i].level);
      stream.writeAttribute("level", tmp);
		 		
      stream.writeAttribute("name", scores[i].name);
      stream.writeEndElement();
	}

   stream.writeEndDocument();
   stream.writeEndDocument();
   file.close();
}

// ------------------------------
// Setters
// ------------------------------

/**
 * Insert new score on the ready place in the list.
 *
 * @param name   The players name.
 * @param level  The level.
 * @param score  The score.
 *
 * @return marker    Location in highscore list.
 */
int HighScore::setScore(QString name, int level, int score)
{
	int marker=-1;
	
	// Find score position
	for(int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		if (score>=scores[i].score)
		{
			marker=i;
			break;
		}
	}
	
	// No highscore
   if (marker==-1) return -1;
	
	// Move all entry on step down.
	for (int i=(MAX_LOCAL_HIGHSCORE-2); i>=marker; i--)
	{
		int offset=i+1;
		scores[offset].score = scores[i].score;
      scores[offset].level = scores[i].level;
		scores[offset].localTime = scores[i].localTime;
      scores[offset].name=scores[i].name;
	}
	
	// Insert now entry.
	scores[marker].score=score;
   scores[marker].level=level;
	scores[marker].localTime=time(NULL);
   scores[marker].name=name;

   return marker;
}


// ------------------------------
// Getters
// ------------------------------

/**
 * Get the name of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The name of the player
 */
QString HighScore::getName(int index)
{
   return scores[index].name;
}

/**
 * Get the date of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The entry date
 */
time_t* HighScore::getDate(int index)
{
	return &scores[index].localTime;
}

/**
 * Get the score of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The score of the selected entry
 */
int HighScore::getScore(int index)
{
	return scores[index].score;
}

/**
 * Get the level of highscore entry X
 *
 * @param index   The range index [0..99]
 *
 * @return The level of the selected entry
 */
int HighScore::getLevel(int index)
{
   return scores[index].level;
}

/**
 * Get the amount of score entries in the highscore array
 *
 * @return amount. The amount of score entries
 */
int HighScore::getAmount(void)
{
	int amount=0;
	for (int i=0; i<MAX_LOCAL_HIGHSCORE; i++)
	{
		if (scores[i].score!=0) amount++;
	}
	return amount;
}

// ------------------------------
// The End
// ------------------------------
