/** 
 *  @file
 *  @brief The file contain the settings methods
 *  @author wplaat
 *
 *  Copyright (C) 2008-2010 PlaatSoft
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
 
#include <mxml.h>

#include "settings.h" 
#include "trace.h"

// -----------------------------------------------------------
// Variables
// -----------------------------------------------------------

char validNick[] = "AAAAAA"; // 6 characters + the trailing NULL (game limit)

// -----------------------------------------------------------
// Internal methodes
// -----------------------------------------------------------
	
/**
 * Get Wii nickname
 * @author Canyon
 * @return the Wii nickname
 */
char *nickName()
{
   char *s_fn="nickName";
   traceEvent(s_fn,0,"enter");
	
	// Name stored on the Wii, size is 0x16 bytes
   unsigned char NickName[22];  
   CONF_GetNickName(NickName);
	
	// Convert to uppercase (game limit)
   char *UpperCaseNick = strupr((char *)NickName); 
 
   unsigned char c, d;
   for(c=0, d=0; c<sizeof(validNick)-1 && d<sizeof(NickName)-1; d++) {
      if((UpperCaseNick[d] >= 0x41 && UpperCaseNick[d] <= 0x5A) ||
         (UpperCaseNick[d] >= 0x30 && UpperCaseNick[d] <= 0x39)) {
			
         // Accept only chars used in the font (uppercase letters + numbers)
         validNick[c++] = UpperCaseNick[d];
      }
   }
	
	traceEvent(s_fn,0,"leave [%s]", validNick);
	return validNick;
}

// -----------------------------------------------------------
// External methodes
// -----------------------------------------------------------

/**
 * Load Settings file 
 * @author wplaat
 * @param filename	The xml setting data
 */
void loadSettingFile(char* filename)
{
   char *s_fn="loadSettingFile";
   traceEvent(s_fn,0,"enter");
   
   int i;
   FILE *fp;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
	char value[MAX_LEN];
	char key[MAX_LEN];
   
   /*Load our xml file! */
   fp = fopen(filename, "r");
   if (fp!=NULL)
   {
		tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
		fclose(fp);

		for(i=0; i<MAX_SETTINGS; i++)
		{
			sprintf(temp, "entry%d", i);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);
  
			tmp=mxmlElementGetAttr(data,"key");   
			if (tmp!=NULL) strcpy(key,tmp); else strcpy(key,"");
		
			tmp=mxmlElementGetAttr(data,"value"); 
			if (tmp!=NULL) strcpy(value,tmp); else strcpy(value,"");
		
			switch (i)
			{
			   case 0:  if (strcmp(key,"NAME")==0)
							{
								strcpy(settings.name,value);
							}
							else
							{
								strcpy(settings.name, nickName());
							}
							traceEvent(s_fn,0,"settings.name=%s",settings.name);
							break;
			
				case 1: 	if (strcmp(key,"MUSIC_VOLUME")==0)
							{
								settings.musicVolume=atoi(value);
							}
							else
							{
								settings.musicVolume=5;
							}
							traceEvent(s_fn,0,"settings.musicVolume=%d",settings.musicVolume);
							break;

				case 2: 	if (strcmp(key,"EFFECT_VOLUME")==0)
							{
								settings.effectVolume=atoi(value);
							}
							else
							{
								settings.effectVolume=5;
							}
							traceEvent(s_fn,0,"settings.effectVolume=%d",settings.effectVolume);
							break;
							
				case 3: 	if (strcmp(key,"GAME_LEVEL")==0)
							{
								settings.gameLevel=atoi(value);
							}
							else
							{
								settings.gameLevel=GAME_LEVEL_MEDIUM;
							}
							traceEvent(s_fn,0,"settings.gameLevel=%d",settings.gameLevel);
							break;
							
				case 4: 	if (strcmp(key,"RANDOM_POSITIONS")==0)
							{
								settings.randomPositions=atoi(value);
							}
							else
							{
								settings.randomPositions=RANDOM_START_POS_NO;
							}
							traceEvent(s_fn,0,"settings.randomPositions=%d",settings.randomPositions);
							break;
							
				case 5: 	if (strcmp(key,"PLAYERS")==0)
							{
								settings.players=atoi(value);
							}
							else
							{
								settings.players=PLAYERS_1;
							}
							traceEvent(s_fn,0,"settings.players=%d",settings.players);
							break;
         }
		} 
   }
   else
   {
		// If file not found, use default values.
		strcpy(settings.name,nickName() );
		settings.musicVolume=5;
		settings.effectVolume=5;	
		settings.gameLevel=GAME_LEVEL_MEDIUM;
		settings.players=PLAYERS_1;	
		settings.randomPositions=RANDOM_START_POS_NO;
   }

   mxmlDelete(data);
   mxmlDelete(tree);
  
   traceEvent(s_fn,0,"leave [void]");
}

/** 
 * Save the setting xml file
 * @author wplaat
 * @param filename	The setting filename.
 */
void saveSettingFile(char* filename)
{
   char *s_fn="saveSettingFile";
   traceEvent(s_fn,0,"enter");
   
   int i;
   mxml_node_t *xml;
   mxml_node_t *group;
   mxml_node_t *data;   
   char temp[MAX_LEN];
      
   xml = mxmlNewXML("1.0");
   
   group = mxmlNewElement(xml, "settings");
   
   for(i=0; i<MAX_SETTINGS; i++)
   {
      sprintf(temp, "entry%d", i);
      data = mxmlNewElement(group, temp);
  
		switch (i)
		{
			case 0:  mxmlElementSetAttr(data, "key", "NAME");	  
						mxmlElementSetAttr(data, "value", settings.name);	
						traceEvent(s_fn,0,"settings.name=%s",settings.name);
						break;
	
			case 1:  sprintf(temp,"%d",settings.musicVolume);
					   mxmlElementSetAttr(data, "key", "MUSIC_VOLUME");	  
						mxmlElementSetAttr(data, "value", temp);	
						traceEvent(s_fn,0,"settings.musicVolume=%d",settings.musicVolume);
						break;
			
			case 2:  sprintf(temp,"%d",settings.effectVolume);
						mxmlElementSetAttr(data, "key", "EFFECT_VOLUME");	  
						mxmlElementSetAttr(data, "value", temp);	
						traceEvent(s_fn,0,"settings.effectVolume=%d",settings.effectVolume);
						break;
						
			case 3:  sprintf(temp,"%d",settings.gameLevel);
						mxmlElementSetAttr(data, "key", "GAME_LEVEL");	  
						mxmlElementSetAttr(data, "value", temp);
					   traceEvent(s_fn,0,"settings.gameLevel=%d",settings.gameLevel);	
						break;
						
			case 4:  sprintf(temp,"%d",settings.randomPositions);
						mxmlElementSetAttr(data, "key", "RANDOM_POSITIONS");	  
						mxmlElementSetAttr(data, "value", temp);	
						traceEvent(s_fn,0,"settings.randomPositions=%d",settings.randomPositions);
						break;
						
			case 5:  sprintf(temp,"%d",settings.players);
						mxmlElementSetAttr(data, "key", "PLAYERS");	  
						mxmlElementSetAttr(data, "value", temp);	
						traceEvent(s_fn,0,"settings.players=%d",settings.players);
						break;
		}
   }
  
   /* now lets save the xml file to a file! */
   FILE *fp;
   fp = fopen(filename, "w");

   mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
   fclose(fp);
   mxmlDelete(data);
   mxmlDelete(group);
   mxmlDelete(xml);
   
   traceEvent(s_fn,0,"leave [void]");
}

// -----------------------------------------------------------
// The End
// -----------------------------------------------------------

 