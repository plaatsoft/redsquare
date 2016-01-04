/**
 *  @file
 *  @brief This file contain all defines
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef _GENERAL_H_
#define _GENERAL_H_

// -----------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------

#include <wiiuse/wpad.h>

#include "GRRLIB.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define PROGRAM_NAME	    		"RedSquare"
#define PROGRAM_VERSION    	"1.00"
#define RELEASE_DATE       	"24-03-2011" 

// Check latest available version 
#define URL1               	"http://www.plaatsoft.nl/service/releasenotes3.html"
#define ID1			        		"UA-6887062-1"

// Fetch Release notes
#define URL2               	"http://www.plaatsoft.nl/service/releasenotes3.html"
#define ID2				    		"UA-6887062-1"

// Set Get Today HighScore
#define URL3               	"http://www.plaatsoft.nl/service/score_set_today.php"
#define ID3				    		"UA-6887062-1"

// Set Get Global HighScore
#define URL4               	"http://www.plaatsoft.nl/service/score_set_global.php"
#define ID4				    		"UA-6887062-1"

#define URL_TOKEN           	" Version "
#define HIGHSCORE_FILENAME  	"sd:/apps/RedSquare/highscore.xml"
#define SETTING_FILENAME    	"sd:/apps/RedSquare/setting.xml"
#define TRACE_FILENAME      	"sd:/apps/RedSquare/RedSquare.trc"
#define GAME_DIRECTORY      	"sd:/apps/RedSquare/"

#define WSP_POINTER_X       	200
#define WSP_POINTER_Y       	250

#define IR_X_OFFSET         	40
#define IR_Y_OFFSET         	40

#define IMAGE_COLOR         	0xFFFFFFFF
#define IMAGE_COLOR2         	0x99999999
#define WHITE_TRANSPARANT		0xFFFFFF88

#define MAX_BUTTONS    	    	20
#define MAX_RUMBLE				4
#define MAX_BLUE_SQUARES   	4
#define MAX_RED_SQUARES   		4
#define MAX_HORZ_PIXELS			640
#define MAX_VERT_PIXELS			480
#define MAX_LOCAL_HIGHSCORE 	100
#define MAX_TODAY_HIGHSCORE 	40
#define MAX_GLOBAL_HIGHSCORE	40
#define MAX_LEN			    	256
#define MAX_ANGLE					360
#define MAX_SOUND_VOLUME		10
#define MAX_MUSIC_TRACK     	9
#define MAX_LINES		    		200
#define MAX_BUFFER_SIZE			8192
#define MAX_SIZE					1
#define MAX_PLAYERS				4

// Enable for WiiMotes and disable Wii BalanceBoard device.
#define MAX_POINTERS				(WPAD_MAX_WIIMOTES-1)

// More then 15 seconds scores are send to the Web services
#define MIN_SCORE		 			15*50 

#define SCROLLBAR_x         	600
#define SCROLLBAR_Y_MIN     	150
#define SCROLLBAR_Y_MAX     	310

#define BALL_X 320
#define BALL_Y 218
#define BALL_SENSE_X 8
#define BALL_SENSE_Y 5

#define MUSIC_MULTIPLER			5
#define EFFECT_MULTIPLER		20

#define BUTTON_A            	(WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_B            	(WPAD_BUTTON_B     | WPAD_CLASSIC_BUTTON_B)
#define BUTTON_HOME         	(WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            	(WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            	(WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)
#define BUTTON_PLUS         	(WPAD_BUTTON_PLUS  | WPAD_CLASSIC_BUTTON_PLUS)

#define GRRLIB_WHITESMOKE   	0xFFFFFFFF
#define GRRLIB_WHITE_TRANS   	0xFFFFFF44
#define GRRLIB_LIGHTRED     	0x3333FFFF
#define GRRLIB_BLACK 			0x000000FF
#define GRRLIB_BLACK_TRANS		0x00000044
#define GRRLIB_BLACK_TRANS_2	0x000000AA
#define GRRLIB_MAROON  			0x800000FF
#define GRRLIB_GREEN   			0x008000FF
#define GRRLIB_OLIVE   			0x808000FF
#define GRRLIB_NAVY    			0x000080FF
#define GRRLIB_PURPLE  			0x800080FF
#define GRRLIB_TEAL    			0x008080FF
#define GRRLIB_GRAY    			0x808080FF
#define GRRLIB_SILVER  			0xC0C0C0FF
#define GRRLIB_RED     			0xFF0000FF
#define GRRLIB_LIME    			0x00FF00FF
#define GRRLIB_YELLOW  			0xFFFF00FF
#define GRRLIB_BLUE    			0x0000FFFF
#define GRRLIB_FUCHSIA 			0xFF00FFFF
#define GRRLIB_AQUA    			0x00FFFFFF
#define GRRLIB_WHITE   			0xFFFFFFFF

// -----------------------------------------------------------
// TYPEDEFS 
// -----------------------------------------------------------

typedef struct 
{
  // png + jpg Image index
  GRRLIB_texImg *logo1;
  GRRLIB_texImg *logo2;
  GRRLIB_texImg *logo3;
  GRRLIB_texImg *logo4;
  GRRLIB_texImg *logo5;	  
  GRRLIB_texImg *logo6;	
  GRRLIB_texImg *logo;
  
  GRRLIB_texImg *redsquare;
  GRRLIB_texImg *bluesquare1;
  GRRLIB_texImg *bluesquare2;
  GRRLIB_texImg *bluesquare3;
  GRRLIB_texImg *bluesquare4;
  
  GRRLIB_texImg *background1;
  GRRLIB_texImg *background3;
  GRRLIB_texImg *intro4;
	
  GRRLIB_texImg *scrollbar;
  GRRLIB_texImg *scrollTop;
  GRRLIB_texImg *scrollMiddle;
  GRRLIB_texImg *scrollBottom;
	
  GRRLIB_texImg *pointer1;
  GRRLIB_texImg *pointer2;
  GRRLIB_texImg *pointer3;
  GRRLIB_texImg *pointer4;
  GRRLIB_texImg *pointer5;
	
  GRRLIB_texImg *button1;
  GRRLIB_texImg *button1select;  
  GRRLIB_texImg *button2;
  GRRLIB_texImg *button2select;  
  GRRLIB_texImg *button3;
  GRRLIB_texImg *button3select;  
  
  GRRLIB_texImg *bar;
  GRRLIB_texImg *barCursor;
  
  GRRLIB_texImg *sound;
  GRRLIB_texImg *star;
} 
image;

image images;

typedef struct
{
   GRRLIB_texImg *image;
   int x;
   int y;
   int width;
   int height;
   bool directionX;
   bool directionY;
	bool visible;
	int player;
} 
square;

square blueSquares[MAX_BLUE_SQUARES+1];
square redSquares[MAX_RED_SQUARES+1];

typedef struct
{
   time_t localTime;
	int    score; 
   int    level;         
   char   name[MAX_LEN];
}
highscore;

highscore highscores[MAX_LOCAL_HIGHSCORE+1];

typedef struct
{
   time_t localTime;
   int    score;
   char   name[MAX_LEN];
	int    level;
   char   location[MAX_LEN];
}
topscore;

topscore todayHighScore[MAX_TODAY_HIGHSCORE+1];
topscore globalHighScore[MAX_GLOBAL_HIGHSCORE+1];


typedef struct
{
   GRRLIB_texImg *image;
   GRRLIB_texImg *imageSelect;
   char name[MAX_LEN]; 
   int x;
   int y;
} 
button;

button buttons[MAX_BUTTONS+1];

typedef struct 
{
  int x;
  int xOffset;
  int y;
  int yOffset;
  int angle;
  int rumble;
  
  GRRLIB_texImg *image;
}
pointer;

pointer pointers[WPAD_MAX_WIIMOTES];

typedef struct
{
  int score;
  int redsquare;
}
player;

player players[MAX_PLAYERS];

struct 
{
  time_t localTime;
  time_t playTime;
  time_t prevPlayTime;
  
  int speed;
  int rating;
  int borderSize;
  int amountOfBlueSquares;
}
game;

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------
 
enum
{
   stateIntro1=0,
   stateIntro2=1,
   stateIntro3=2,
	stateIntro4=3,
   stateMenu=4,
   stateGame=5,
   stateGameOver=6,
   stateLocalHighScore=7,
   stateTodayHighScore=8,
   stateGlobalHighScore=9,
   stateHelp1=10,
	stateHelp2=11,
   stateCredits=12,
   stateReleaseNotes=13,
	stateSoundSettings=14,
   stateGameSettings=15,
	stateDonate=16,
   stateNone=17,
	stateQuit=18
};

enum
{
   fontTitle1=0,
   fontTitle2=1,
   fontSubTitle=2,
   fontParagraph=3,
   fontNormal=4,
   fontSpecial=5,
   fontNew=6,
   fontButton=7,
   fontWelcome=8
};

#endif

/**
 * @mainpage Wii RedSquare Documentation
 * @image html RedSquare.png
 * Welcome to the RedSquare documentation.
 *
 * @section Introduction
 * RedSquare is a 2D classic game for the Nintendo Wii. Click and hold 
 * the red square. Now, move so that you neither touch the walls nor 
 * get hit by any of the blue blocks. If you make it to 31 seconds, 
 * you are doing brilliantly!
 *
 * @section Links
 * Website: http://www.plaatsoft.nl\n
 * Code: http://code.google.com/p/redsquare\n
 *
 * @section Credits
 * Documentation: wplaat\n
 *
 * @section WishList
 *  - Adding Wii Balanceboard support 
 * 
 * @section ReleaseNotes
 *
 * <b>24-03-2011 Version 1.00</b>
 * - GUI:
 *  - Update menu screen information.
 * - Core:
 *  - Optimise game core
 *  - Added intro screen 4. WarQuest game info.
 * - General:
 *  - Build game with devkitPPC r21 compiler.
 *
 *
 * <b>13-09-2010 Version 0.99</b>
 * - GUI:
 *  - Update menu screen information.
 * - Core:
 *  - Solve random freeze problem during startup of game.
 * - General:
 *  - Build game with devkitPPC r21 compiler.
 *
 *  <b>11-09-2010 Version 0.98</b>
 *  - GUI:
 *   - Update menu screen information.
 *   - Overall FPS has improved 50 percent. Thanks Crayon
 *  - Core:
 *   - Use GRRLIB 4.3.0 as graphical engine.
 *   - libpng was updated to version 1.4.2
 *   - libjpeg was updated to version 8b
 *   - zlib was updated to version 1.2.5
 *   - FreeType was updated to 2.3.12
 *  - General:
 *   - Maintenance release.
 *   - Build game with devkitPPC r21 compiler.
 *
 *  <b>31-03-2010 Version 0.97</b>
 *  - GUI:
 *    - Show played game level on high score screens.
 *    - Update menu screen information.
 *  - Core:
 *   - Improve stability.
 *   - WiiMote timeout increase from 60 to 300 seconds.
 *   - Use libfat 1.0.7 as disk access engine.
 *   - Use libogc 1.8.3 as Wii interface engine
 *  - General:
 *   - Make source code compliant with r21 compiler.
 *   - Build game with devkitPPC r21 compiler.
 *
 *  <b>02-03-2010 Version 0.96</b>
 *  - GUI:
 *   - Improve local high score screen. Add score stars.
 *   - Improve game over screen. Add score stars.
 *   - Added three extra game settings buttons.
 *   - Improve square images.
 *   - Update menu screen information.
 *   - Disable Wii DVD light thread. Not stable.
 *  - Core:
 *   - Added support for maximum four concurrent players. 
 *   - Added game level: Easy, Medium and Hard.
 *    - Gameboard border size is now related to selected game level.
 *    - Amount of blue squares is now related to selected game level.
 *   - Start position of blue squares can now be randomized. 
 *   - Enable A and B button to select red square during game.
 *   - Press Home button to go back to the main menu.
 *  - General:
 *   - Added screenshots to source code documentation.
 *   - Improve debug trace information.
 *   - Build game with devkitPPC r19 compiler.
 *
 *  <b>11-02-2010 Version 0.95</b>
 *  - GUI:
 *   - Added Wii DVD light effects to game.
 *   - Improve game settings screen.
 *   - Added donate screen.
 *   - Added scrollbar to highscore and release notes screens.
 *   - The 100th highest local scores are showed.
 *   - The 40th highest today and global high scores are showed.
 *   - Added to most screens network status information.
 *  - Core:
 *   - Extend user name from 3 to 6 characters.
 *   - Default user name is based on Wii nickname.
 *   - Increase http buffer size from 8kb to 10kb.
 *   - Bug fix: Http thread memory cleanup is not correctly executed.
 *  - General: 
 *   - Added source code to Google Code repository.
 *   - Added source code documentation (Javadoc style).
 *   - With the doxygen tool the documentation can be generated.
 *   - Build game with devkitPPC r19 compiler.
 *
 *  <b>11-01-2010 Version 0.94</b>
 *  - GUI:
 *   - Add WiiMote control help screen.
 *   - Add improve gameover screen.
 *  - Core:
 *   - Add improve score calculation.
 *   - Improve webservice call to store highscore.
 *   - Added support for 60HZ (640x480) TV Mode.
 *   - Use libogc 1.8.1 library as Wii interface engine.
 *   - Use GRRLIB v4.2.0 as graphical engine.
 *  - General: 
 *   - Build game with devkitPPC r19 compiler.
 *
 *  <b>19-11-2009 Version 0.93</b>
 *  - GUI:
 *   - Added today top highscore screen.
 *   - Improve local and global highscore screen.
 *  - Core:
 *   - Sound volume settings are now saved!
 *   - Added functionality to trace game events to trace file.
 *   - High score is send to web service if score is better then 500 points.
 *   - Improve network thread
 *   - Use libfat 1.0.6 as disk access engine.
 *   - Use libmxml 2.6 library as xml engine.
 *   - Use libogc 1.8.0 library as Wii interface engine.
 *  - General: 
 *   - Build game with devkitPPC r19 compiler.
 *
 *  <b>17-09-2009 Version 0.92</b>
 *  - GUI:
 *   - Improve intro screens.
 *  - Core:
 *   - Use the asndlib (part of libogc) now as standard sound engine.
 *   - Use libfat 1.0.4 as disk access engine.
 *   - Use libogc 1.7.1a as Wii interface engine.
 *  - General:
 *   - Maintenance release.
 *   - Build game with devkitPPC r17 compiler.
 * 
 *  <b>08-03-2009 Version 0.91</b>
 *  - GUI:
 *   - Improve intro screens.
 *   - show play time on game board.
 *   - Added fps information on screen.
 *  - Core:
 *   - Added new GRRLIB v4.0 library as graphical render engine.
 *   - Added screenshot functionality with plus button.
 *   - Pictures are store on the SdCard (sd:/apps/RedSquare)
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>08-02-2009 Version 0.90</b>
 *  - GUI:
 *   - Added game settings screen.
 *   - Improve Local and Global highscore screen.
 *   - Improve third intro screen.
 *   - Bug fix: menu screen graphical error solved.
 *  - Core:
 *   - Added load/save game setting to sdcard.
 *   - Increase http receive buffer size to 8kb.
 *   - Use only one unique cookie number during the game.
 *   - High score is send to web service if score is better then 40 seconds.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>15-01-2009 Version 0.80</b>
 *  - GUI:
 *   - Bug fix: Remove some small reported graphical bugs.
 *   - update urls on intro screens to www.plaatsoft.nl (My new domain on internet)
 *   - Network thread status is now showed on the welcome screen.
 *   - Updated credits screen information.
 *   - Updated help screen information.
 *  - Core:
 *   - Improve and secure webservice interface.
 *   - Bug fix: Remove several bugs in network thread.
 *   - Bug fix: google analysic requests are now working again.
 *   - Bug fix: Score cheating with 1 and 2 button is now not posible anymore.
 *   - Improve sound effects (Thanks nowhereman)
 *   - Bug fix: Global highscore xml data is now always processed right.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>01-01-2009 Version 0.70</b>
 *  - GUI:
 *   - Added global highscore screen.
 *   - Improve button graphics.
 *   - Improve release notes screen.
 *  - Core:
 *   - Global highscore information is fetch from internet.
 *   - Added new cool background music.
 *   - Network thread status is displayed on welcome screen.
 *   - Bug fix: Local highscore is now always loaded correctly.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>20-12-2008 Version 0.60</b>
 *  - GUI:
 *   - Improve screen title design.
 *  - Core:
 *   - Added SDHC card support.
 *   - Added power button support.
 *   - Default effect volume adapted.
 *   - Bug fix: IR pointer doesn't disappear anymore.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>08-12-2008 Version 0.50</b>
 *  - GUI:
 *   - Added sound setting screen.
 *   - Added release notes screen.
 *  - Core:
 *   - Added functionality to fetch release notes from internet.
 *   - Added send highscore to google analytic.
 *   - Added 9 music tracks.
 *  - General:
 *   - First release for Wii homebrew scene.
 *   - Build game devkitPPC r15 compiler.
 *
 *  <b>05-12-2008 Version 0.40</b>
 *  - GUI:
 *   - Added welcome screen.
 *   - Added help screen.
 *   - Added credits screen.
 *  - Core:
 *   - Added exit to HBC functionality.
 *   - Added reset Wii functionality.
 *  - General:
 *   - Internal release
 *   - Build game with devkitPPC r15 compiler.
 *
 *  <b>04-12-2008 Version 0.30</b>
 *  - GUI:
 *   - Added local highScore screen.
 *  - Core:
 *   - Store highscore (in xml format) on SD Card .
 *   - Added google analytic http request.
 *  - General:
 *   - Internal release
 *   - Build game with devkitPPC r15 compiler.
 *
 *  <b>02-12-2008 Version 0.20</b>
 *  - GUI: 
 *   - Complete redesign of gameboard graphics.
 *  - Core:
 *   - Added new version http request check.
 *   - Remove some minor reported bugs.
 *   - Add background music.
 *   - Add some sound effects.
 *  - General:
 *   - Internal release
 *   - Build game with devkitPPC r15 compiler.
 *
 *  <b>29-11-2008 Version 0.10</b>
 *  - GUI:
 *   - Gameboard design.
 *   - Added three intro screens.
 *  - Core:
 *   - Added WiiRemote IR control.
 *   - Basic game engine ready.
 *  - General:
 *   - Started programming.
 *   - Build game with devkitPPC r15 compiler.
 *
 * @section ScreenShots
 * This section contain some screenshots of the game.
 * - <a href="../screenshots/RedSquare-intro1.jpg">Intro Screen 1</a>
 * - <a href="../screenshots/RedSquare-intro2.jpg">Intro Screen 2</a>
 * - <a href="../screenshots/RedSquare-intro3.jpg">Intro Screen 3</a>
 * - <a href="../screenshots/RedSquare-menu.jpg">Menu Screen</a>
 * - <a href="../screenshots/RedSquare-game1.jpg">Game Screen 1</a>
 * - <a href="../screenshots/RedSquare-game2.jpg">Game Screen 2</a>
 * - <a href="../screenshots/RedSquare-gameover.jpg">Game Over screen</a>
 * - <a href="../screenshots/RedSquare-highscore1.jpg">Local Highscore screen</a>
 * - <a href="../screenshots/RedSquare-highscore2.jpg">Today Highscore screen</a>
 * - <a href="../screenshots/RedSquare-highscore3.jpg">Global Highscore screen</a>
 * - <a href="../screenshots/RedSquare-help1.jpg">Help 1 screen</a>
 * - <a href="../screenshots/RedSquare-help2.jpg">Help 2 screen </a>
 * - <a href="../screenshots/RedSquare-credits.jpg">Credits screen</a>
 * - <a href="../screenshots/RedSquare-releasenotes.jpg">Release Notes screen</a>
 * - <a href="../screenshots/RedSquare-soundsettings.jpg">Sound Settings screen</a>
 * - <a href="../screenshots/RedSquare-gamesettings.jpg">Game Settings screen</a>
 * - <a href="../screenshots/RedSquare-donate.jpg">Donate screen</a>
 *
 * @section Licence
 * <b>Copyright (c) 2008-2010 Plaatsoft</b>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
// -----------------------------------------------------------
// The End
// -----------------------------------------------------------