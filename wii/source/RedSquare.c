/** 
 *  @file
 *  @brief Wii RedSquare game core
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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include <math.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h> 
#include <fcntl.h>
#include <unistd.h>
#include <time.h> 
#include <asndlib.h>
#include <ogc/audio.h>
#include <fat.h>
#include <mxml.h>
#include <ogc/lwp_watchdog.h>	


#include "effect1_pcm.h"
#include "effect2_pcm.h"
#include "effect3_pcm.h"
#include "topscore_pcm.h"

#include "track1_mod.h"
#include "track2_mod.h"
#include "track3_mod.h"
#include "track4_mod.h"
#include "track5_mod.h"
#include "track6_mod.h"
#include "track7_mod.h"
#include "track8_mod.h"
#include "track9_mod.h"

#include "general.h"
#include "http.h"
#include "trace.h"
#include "light.h"
#include "settings.h"
#include "font_ttf.h" 

// Enable / Disable Wii DVD Drive lights effects.
#define LIGHT(X) 

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

u32     *frameBuffer[1] = {NULL};
GXRModeObj *rmode = NULL;
Mtx     GXmodelView2D;

int     yOffset              = 0;
int     angle                = 0;
float   size                 = 0;
float   wave1                = 0;
float   wave2                = 0;
bool    selected1				  = false;
bool    selected2				  = false;
int     stateMachine         = stateIntro1;
int     prevStateMachine     = stateNone;
int     maxLocalHighScore    = 0; 
int     maxTodayHighScore    = 0;
int     maxGlobalHighScore   = 0;
int     maxButtons           = 0;
int     selectedMusic        = 1;
int     notesStartLine       = 0;
int     noteDelay            = 0;
int     scrollIndex       	  = 0;
int 	  lightValue			  = 0;
bool	  lightUp				  = true;

static  MODPlay snd1;
char    appl_user3[MAX_LEN];

// Poweroff flag
bool bPowerOff = false;	

// logo1 Image
extern const unsigned char pic1data[];
extern const int           pic1length;

// logo2 Image
extern const unsigned char pic2data[];
extern const int           pic2length;

// logo3 Image
extern const unsigned char pic3data[];
extern const int           pic3length;

// RedSquare1 Image
extern const unsigned char pic4data[];
extern const int           pic4length;

// BlueSquare1 Image
extern const unsigned char pic5data[];
extern const int           pic5length;

// BlueSquare2 Image
extern const unsigned char pic6data[];
extern const int           pic6length;

// BlueSquare3 Image
extern const unsigned char pic7data[];
extern const int           pic7length;

// BlueSquare4 Image
extern const unsigned char pic8data[];
extern const int           pic8length;

// background1 Image
extern const unsigned char pic10data[];
extern const int           pic10length;

// Intro4 Image
extern const unsigned char pic1000data[];
extern const int      		pic1000length;


// Golden Star Image
extern const unsigned char pic14data[];
extern const int           pic14length;

// bar Image
extern const unsigned char pic17data[];
extern const int           pic17length;
 
// barCursor Image
extern const unsigned char pic18data[];
extern const int           pic18length;



// Button1 Image
extern const unsigned char pic12data[];
extern const int           pic12length;

// Button1select Image
extern const unsigned char pic13data[];
extern const int           pic13length;

// Button2 Image
extern const unsigned char pic19data[];
extern const int           pic19length;

// Button2select Image
extern const unsigned char pic20data[];
extern const int           pic20length;

// Button3 Image
extern const unsigned char pic37data[];
extern const int           pic37length;

// Button3select Image
extern const unsigned char pic38data[];
extern const int           pic38length;



// Sound Image
extern const unsigned char pic21data[];
extern const int           pic21length;

// Panel Image
extern const unsigned char pic22data[];
extern const int           pic22length;

// Logo4 Image
extern const unsigned char pic23data[];
extern const int           pic23length;

// Logo5 Image
extern const unsigned char pic24data[];
extern const int           pic24length;

// background3 Image
extern const unsigned char pic25data[];
extern const int           pic25length;

// logo6 Image
extern const unsigned char pic26data[];
extern const int           pic26length;

// Scrollbar image
extern const unsigned char pic33data[];
extern const int           pic33length;

// ScrollTop image
extern const unsigned char pic34data[];
extern const int           pic34length;

// ScrollMiddle image
extern const unsigned char pic35data[];
extern const int           pic35length;

// scrollBottom image
extern const unsigned char pic36data[];
extern const int           pic36length;



// Pointer1 Image (WiiMote 1)
extern const unsigned char pic40data[];
extern const int           pic40length;

// Pointer2 Image (WiiMote 2)
extern const unsigned char pic41data[];
extern const int           pic41length;

// Pointer3 Image (WiiMote 3)
extern const unsigned char pic42data[];
extern const int           pic42length;

// Pointer4 Image (WiiMote 4)
extern const unsigned char pic43data[];
extern const int           pic43length;

// Pointer5 Image (Balance Board)
extern const unsigned char pic44data[];
extern const int           pic44length;

GRRLIB_ttfFont *myFont; 

// -----------------------------------------------------------
// GAME LOGIC
// -----------------------------------------------------------

/**
 * Get next of previous letter or number.
 *
 * @author wplaat
 *
 * @param letter 	The letter
 * @param up		The next letter (true) previous letter (false)
 *
 * @return letter 
 */
char getLetter(char letter, bool up)
{
	if (up)
	{	
		if (letter==90) return '0';
		if (letter==57) return 'A';
		return ++letter;				
	}
	else
	{	
		if (letter==65) return '9';
		if (letter==48) return 'Z';
		return --letter;					
	}
}

/**
 * Calculate Frame Per Second Rate 
 *
 * @author wplaat
 */
static u8 calculateFrameRate() 
{
    static u8 frameCount = 0;
    static u32 lastTime;
    static u8 FPS = 0;
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - lastTime > 1000) {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}

/**	
 * PowerOff callback function.
 * 
 * @author wplaat
 */
void doPowerOff( void )
{
   char *s_fn="doPowerOff";
   traceEvent(s_fn,0,"enter");
	
	bPowerOff = true;
	stateMachine=stateQuit;
	
	traceEvent(s_fn,0,"leave [void]");
	return;
}

/**
 * PowerOff callback function for the Wii Remote power button.
 * 
 * @author wplaat 
 */
void doPadPowerOff( s32 chan )
{
   char *s_fn="doPadPowerOff";
   traceEvent(s_fn,0,"enter");
   
	if ( chan == WPAD_CHAN_ALL )
	{
		bPowerOff = true;
	}
	
	traceEvent(s_fn,0,"leave [void]");
	return;
}


// -----------------------------------------------------------
// Init methods
// -----------------------------------------------------------

/**
 * Init game images
 * 
 * @author wplaat
 */
void initImages(void)
{
   char *s_fn="initImages";
   traceEvent(s_fn,0,"enter");
	
   images.logo1=GRRLIB_LoadTexture( pic1data );
	GRRLIB_SetMidHandle( images.logo1, true );
	
   images.logo2=GRRLIB_LoadTexture( pic2data );
   images.logo3=GRRLIB_LoadTexture( pic3data );
   images.logo4=GRRLIB_LoadTexture( pic23data );
   images.logo5=GRRLIB_LoadTexture( pic24data );   
   images.logo6=GRRLIB_LoadTexture( pic26data );   
	
	images.intro4=GRRLIB_LoadTexture( pic1000data );  
	 
	images.logo=GRRLIB_LoadTexture( pic2data );
   GRRLIB_InitTileSet(images.logo, images.logo->w, 1, 0);
      
   images.redsquare=GRRLIB_LoadTexture( pic4data );
   images.bluesquare1=GRRLIB_LoadTexture( pic5data );
   images.bluesquare2=GRRLIB_LoadTexture( pic6data );
   images.bluesquare3=GRRLIB_LoadTexture( pic7data );
   images.bluesquare4=GRRLIB_LoadTexture( pic8data );
   
	images.pointer1=GRRLIB_LoadTexture( pic40data );
	images.pointer2=GRRLIB_LoadTexture( pic41data );
	images.pointer3=GRRLIB_LoadTexture( pic42data );
	images.pointer4=GRRLIB_LoadTexture( pic43data );
	images.pointer5=GRRLIB_LoadTexture( pic44data );

   images.background1=GRRLIB_LoadTexture( pic10data );
   images.background3=GRRLIB_LoadTexture( pic25data );
	  
   images.button1=GRRLIB_LoadTexture( pic12data );
   images.button1select=GRRLIB_LoadTexture( pic13data );     	
   images.button2=GRRLIB_LoadTexture( pic19data );
   images.button2select=GRRLIB_LoadTexture( pic20data );  
   images.button3=GRRLIB_LoadTexture( pic37data );
   images.button3select=GRRLIB_LoadTexture( pic38data ); 
	
   images.bar=GRRLIB_LoadTexture( pic17data ); 
   images.barCursor=GRRLIB_LoadTexture( pic18data );

   images.scrollbar=GRRLIB_LoadTexture(pic33data);
   images.scrollTop=GRRLIB_LoadTexture( pic34data);
   images.scrollMiddle=GRRLIB_LoadTexture( pic35data);
   images.scrollBottom=GRRLIB_LoadTexture( pic36data);
   
	images.sound=GRRLIB_LoadTexture( pic21data );    
	GRRLIB_SetMidHandle( images.sound, true );
	
	images.star=GRRLIB_LoadTexture( pic14data );  
	GRRLIB_SetMidHandle( images.star, true ); 	 
   
   traceEvent(s_fn,0,"leave [void]");
}


/**
 * Initiase Pointers
 *
 * @author wplaat
 */
void initPointers(void)
{
	char *s_fn="initPointers";
   traceEvent(s_fn,0,"enter");
	
	// WiiMote 1
	pointers[0].image=images.pointer1;
	
	// WiiMote 2
	pointers[1].image=images.pointer2;
	
	// WiiMote 3
	pointers[2].image=images.pointer3;
	
	// WiiMote 4
	pointers[3].image=images.pointer4;
	
	// Wii balanceboard
	pointers[4].image=images.pointer5;
	
	traceEvent(s_fn,0,"leave [void]");
}	

/**
 * Initiase Music track 
 *
 * @author wplaat
 */
void initMusicTrack(void)
{
   char *s_fn="initMusicTrack";
   traceEvent(s_fn,0,"enter");
   
   switch (selectedMusic)
   {
      case 1 : MODPlay_SetMOD(&snd1, track1_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
      case 2 : MODPlay_SetMOD(&snd1, track2_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 3 : MODPlay_SetMOD(&snd1, track3_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 4 : MODPlay_SetMOD(&snd1, track4_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 5 : MODPlay_SetMOD(&snd1, track5_mod);
			   MODPlay_Start(&snd1);	
			   break;	
		   
	  case 6 : MODPlay_SetMOD(&snd1, track6_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 7 : MODPlay_SetMOD(&snd1, track7_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 8 : MODPlay_SetMOD(&snd1, track8_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 9 : MODPlay_SetMOD(&snd1, track9_mod);
			   MODPlay_Start(&snd1);	
			   break;
   } 
   MODPlay_SetVolume( &snd1, settings.musicVolume*MUSIC_MULTIPLER,settings.musicVolume*MUSIC_MULTIPLER); 
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Init Sound layer
 *
 * @author wplaat
 */
void initSound(void)
{
   char *s_fn="initSound";
   traceEvent(s_fn,0,"enter");
   
   // Init Sound engine	
   SND_Init(INIT_RATE_48000); 
   MODPlay_Init(&snd1);
   SND_Pause(0);
   
   initMusicTrack();	
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Init TCP network thread
 * @author wplaat 
 */
void initThreads(void)
{ 
   char *s_fn="initThreads";
   traceEvent(s_fn,0,"enter");
  
   char userData1[MAX_LEN];
   char userData2[MAX_LEN];

   // Set userData1   		 
   memset(userData1,0x00,sizeof(userData1));
   sprintf(userData1,"%s=%s",
				PROGRAM_NAME,
				PROGRAM_VERSION);
		
   // Get userData2 
   memset(userData2,0x00,sizeof(userData2));
   sprintf(userData2,"appl=%s&level=%d",
				PROGRAM_NAME,
				settings.gameLevel);
	   
   tcp_init_layer();

   tcp_start_thread(PROGRAM_NAME, PROGRAM_VERSION, 
					 ID1, URL1, 
					 ID2, URL2, 
					 ID3, URL3, 
					 ID4, URL4, 
					 URL_TOKEN, 
					 userData1, 
					 userData2);

   traceEvent(s_fn,0,"leave [void]");
}

/** 
 * initiase Buttons on screen
 *
 * @author wplaat
 */
void initButtons(void)
{ 
	char *s_fn="initButtons";
   traceEvent(s_fn,0,"enter");
	
   switch (stateMachine)
   {
      case stateMenu:
      {
			maxButtons=10;

			int ypos=30+yOffset;
		 
			// Play button 
			buttons[0].image=images.button1;
			buttons[0].imageSelect=images.button1select;
			strcpy(buttons[0].name,"Play");
			buttons[0].x=370;
			buttons[0].y=ypos;
   
			ypos+=40;
			
			// High Score button 
			buttons[1].image=images.button1;
			buttons[1].imageSelect=images.button1select;
			strcpy(buttons[1].name,"High Score");   
			buttons[1].x=370;
			buttons[1].y=ypos;
   
			ypos+=40;
			
			// Help button 
			buttons[2].image=images.button1;
			buttons[2].imageSelect=images.button1select;
			strcpy(buttons[2].name,"Help" );
			buttons[2].x=370;
			buttons[2].y=ypos;
   
			ypos+=40;
			
			// Credits button 
			buttons[3].image=images.button1;
			buttons[3].imageSelect=images.button1select;
			strcpy(buttons[3].name,"Credits" );
			buttons[3].x=370;
			buttons[3].y=ypos;

			ypos+=40;
			
			// Release Notes button 
			buttons[5].image=images.button1;
			buttons[5].imageSelect=images.button1select;
			strcpy(buttons[5].name,"Release Notes" );
			buttons[5].x=370;
			buttons[5].y=ypos;
   
			ypos+=40;
			
			// Sound button 
			buttons[4].image=images.button1;
			buttons[4].imageSelect=images.button1select;
			strcpy(buttons[4].name,"Sound Settings" );
			buttons[4].x=370;
			buttons[4].y=ypos;
						
			ypos+=40;
			
			// Game Settings button 
			buttons[6].image=images.button1;
			buttons[6].imageSelect=images.button1select;
			strcpy(buttons[6].name,"Game Settings" );
			buttons[6].x=370;
			buttons[6].y=ypos;
		
			ypos+=40;
		
			// Game Settings button 
			buttons[7].image=images.button1;
			buttons[7].imageSelect=images.button1select;
			strcpy(buttons[7].name,"Donate" );
			buttons[7].x=370;
			buttons[7].y=ypos;
		
		
			// Exit HBC button 
			buttons[8].image=images.button1;
			buttons[8].imageSelect=images.button1select;
			strcpy(buttons[8].name,"Exit to HBC" );
			buttons[8].x=370;
			buttons[8].y=380+yOffset;
      
			// Reset Wii button 
			buttons[9].image=images.button1;
			buttons[9].imageSelect=images.button1select;
			strcpy(buttons[9].name,"Reset Wii" );
			buttons[9].x=370;
			buttons[9].y=420+yOffset;
		}
      break;
	  
    case stateLocalHighScore:
	  {
	    maxButtons=2;

		// Next button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Next");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
		
		// Scrollbar button 
		buttons[1].image=images.scrollbar;
		buttons[1].imageSelect=images.scrollbar;
		strcpy(buttons[1].name,"");
		buttons[1].x=SCROLLBAR_x;
		buttons[1].y=SCROLLBAR_Y_MIN;
	  }
	  break;
	  
	case stateTodayHighScore:
	  {
	    maxButtons=2;

		// Next button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Next");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
		
		// Scrollbar button 
		buttons[1].image=images.scrollbar;
		buttons[1].imageSelect=images.scrollbar;
		strcpy(buttons[1].name,"");
		buttons[1].x=SCROLLBAR_x;
		buttons[1].y=SCROLLBAR_Y_MIN;
	  }
	  break;
	 
	case stateGlobalHighScore:
	  {
	    maxButtons=2;

		// Next button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Next");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
		
		// Scrollbar button 
		buttons[1].image=images.scrollbar;
		buttons[1].imageSelect=images.scrollbar;
		strcpy(buttons[1].name,"");
		buttons[1].x=SCROLLBAR_x;
		buttons[1].y=SCROLLBAR_Y_MIN;
	  }
	  break;
	  
	case stateHelp1:
	  {
	    maxButtons=1;

		// Back button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Next");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
	  }
	  break;

	case stateHelp2:
	  {
	    maxButtons=1;

		// Back button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Back");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
	  }
	  break;
	  
	case stateCredits:
	  {
	    maxButtons=1;

		// Back button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Back");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
	  }
	  break;
	  
	case stateSoundSettings:
      {
        maxButtons=7;

		// Music Volume - button 
		buttons[0].image=images.button2;
		buttons[0].imageSelect=images.button2select;
		strcpy(buttons[0].name,"-");
		buttons[0].x=20;
		buttons[0].y=155+yOffset;
   
		// Music Volume + button 
		buttons[1].image=images.button2;
		buttons[1].imageSelect=images.button2select;
		strcpy(buttons[1].name,"+");   
		buttons[1].x=540;
		buttons[1].y=155+yOffset;
		
		// Effect Volume - button 
		buttons[2].image=images.button2;
		buttons[2].imageSelect=images.button2select;
		strcpy(buttons[2].name,"-");
		buttons[2].x=20;
		buttons[2].y=255+yOffset;
   
		// Effect Volume + button 
		buttons[3].image=images.button2;
		buttons[3].imageSelect=images.button2select;
		strcpy(buttons[3].name,"+");   
		buttons[3].x=540;
		buttons[3].y=255+yOffset;
		
		// Music track - button 
		buttons[4].image=images.button2;
		buttons[4].imageSelect=images.button2select;
		strcpy(buttons[4].name,"-");
		buttons[4].x=140;
		buttons[4].y=335+yOffset;

		// Music track + button 
		buttons[5].image=images.button2;
		buttons[5].imageSelect=images.button2select;
		strcpy(buttons[5].name,"+");   
		buttons[5].x=420;
		buttons[5].y=335+yOffset;
		
		// Back button 
		buttons[6].image=images.button1;
		buttons[6].imageSelect=images.button1select;
		strcpy(buttons[6].name,"Back");
		buttons[6].x=200;
		buttons[6].y=425+yOffset;
	  }
	  break;
   
      case stateReleaseNotes:
	  {
	    maxButtons=2;
	  		
		// Back button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Back");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
		
		// Scrollbar button 
		buttons[1].image=images.scrollbar;
		buttons[1].imageSelect=images.scrollbar;
		strcpy(buttons[1].name,"");
		buttons[1].x=SCROLLBAR_x;
		buttons[1].y=SCROLLBAR_Y_MIN;		
	  }
	  break;
	  
	  case stateGameSettings:
	  {
	   maxButtons=16;
		int xOffset=50;
		
	   // First letter + button 
		buttons[0].image=images.button2;
		buttons[0].imageSelect=images.button2select;
		strcpy(buttons[0].name,"+");
		buttons[0].x=xOffset;
		buttons[0].y=155+yOffset;
   
		// First letter - button 
		buttons[1].image=images.button2;
		buttons[1].imageSelect=images.button2select;
		strcpy(buttons[1].name,"-");   
		buttons[1].x=xOffset;
		buttons[1].y=270+yOffset;
				
		xOffset+=90;
		
		// Second letter + button 
		buttons[2].image=images.button2;
		buttons[2].imageSelect=images.button2select;
		strcpy(buttons[2].name,"+");
		buttons[2].x=xOffset;
		buttons[2].y=155+yOffset;
   
		// Second letter - button 
		buttons[3].image=images.button2;
		buttons[3].imageSelect=images.button2select;
		strcpy(buttons[3].name,"-");   
		buttons[3].x=xOffset;
		buttons[3].y=270+yOffset;
				
		xOffset+=90;
		
		// Third letter + button 
		buttons[4].image=images.button2;
		buttons[4].imageSelect=images.button2select;
		strcpy(buttons[4].name,"+");
		buttons[4].x=xOffset;
		buttons[4].y=155+yOffset;
   
		// Third letter - button 
		buttons[5].image=images.button2;
		buttons[5].imageSelect=images.button2select;
		strcpy(buttons[5].name,"-");   
		buttons[5].x=xOffset;
		buttons[5].y=270+yOffset;
		
		xOffset+=90;
		
		// Fourth letter + button 
		buttons[6].image=images.button2;
		buttons[6].imageSelect=images.button2select;
		strcpy(buttons[6].name,"+");
		buttons[6].x=xOffset;
		buttons[6].y=155+yOffset;
   
		// Fourth letter - button 
		buttons[7].image=images.button2;
		buttons[7].imageSelect=images.button2select;
		strcpy(buttons[7].name,"-");   
		buttons[7].x=xOffset;
		buttons[7].y=270+yOffset;
		
		xOffset+=90;
		
		// Fifth letter + button 
		buttons[8].image=images.button2;
		buttons[8].imageSelect=images.button2select;
		strcpy(buttons[8].name,"+");
		buttons[8].x=xOffset;
		buttons[8].y=155+yOffset;
   
		// Fitth letter - button 
		buttons[9].image=images.button2;
		buttons[9].imageSelect=images.button2select;
		strcpy(buttons[9].name,"-");   
		buttons[9].x=xOffset;
		buttons[9].y=270+yOffset;
		
		xOffset+=90;
		
		// Sixth letter + button 
		buttons[10].image=images.button2;
		buttons[10].imageSelect=images.button2select;
		strcpy(buttons[10].name,"+");
		buttons[10].x=xOffset;
		buttons[10].y=155+yOffset;
   
		// Sixth letter - button 
		buttons[11].image=images.button2;
		buttons[11].imageSelect=images.button2select;
		strcpy(buttons[11].name,"-");   
		buttons[11].x=xOffset;
		buttons[11].y=270+yOffset;
	
		// Amount of players button
		buttons[12].image=images.button3;
		buttons[12].imageSelect=images.button3select;
		switch(settings.players)
		{
			case PLAYERS_1: 
						strcpy(buttons[12].name,"1 WiiMote"); 
						break;
						
			case PLAYERS_2: 
						strcpy(buttons[12].name,"2 WiiMotes"); 
						break;
						
			case PLAYERS_3: 
						strcpy(buttons[12].name,"3 WiiMotes"); 
						break;
						
			case PLAYERS_4: 
						strcpy(buttons[12].name,"4 WiiMotes"); 
						break;
						
			case PLAYER_BALANCEBOARD: 
						strcpy(buttons[12].name,"Balanceboard"); 
						break;
		}		
		buttons[12].x=45;
		buttons[12].y=375+yOffset;		
		
		// Game Level button 
		buttons[13].image=images.button3;
		buttons[13].imageSelect=images.button3select;
		switch(settings.gameLevel)
		{
			case GAME_LEVEL_EASY: 
						strcpy(buttons[13].name,"Easy"); 
						break;
						
			case GAME_LEVEL_MEDIUM: 
						strcpy(buttons[13].name,"Medium"); 
						break;
						
			case GAME_LEVEL_HARD: 
						strcpy(buttons[13].name,"Hard"); 
						break;
		}		
		buttons[13].x=(MAX_HORZ_PIXELS/2)-(images.button3->w/2)-5;
		buttons[13].y=375+yOffset;
		
		// Randomize blue square start position button option
		buttons[14].image=images.button3;
		buttons[14].imageSelect=images.button3select;
		switch(settings.randomPositions)
		{
			case RANDOM_START_POS_NO: 
						strcpy(buttons[14].name,"No"); 
						break;
						
			case RANDOM_START_POS_YES: 
						strcpy(buttons[14].name,"Yes"); 
						break;
		}		
		buttons[14].x=MAX_HORZ_PIXELS-55-images.button3->w;
		buttons[14].y=375+yOffset;
				
		// Back button 
		buttons[15].image=images.button1;
		buttons[15].imageSelect=images.button1select;
		strcpy(buttons[15].name,"Back");	
		buttons[15].x=200;
		buttons[15].y=425+yOffset;	
	  }
	  break;
	  
	  case stateDonate:
	  {
	    maxButtons=1;

		// Back button 
		buttons[0].image=images.button1;
		buttons[0].imageSelect=images.button1select;
		strcpy(buttons[0].name,"Back");
		buttons[0].x=200;
		buttons[0].y=425+yOffset;
	  }
	  break;
   }
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Init Today Highscore
 * 
 * @author wplaat
 */
void initTodayHighScore(void)
{
	char *s_fn="initTodayHighScore";
	traceEvent(s_fn,0,"enter");
	
	int i;   

	// Clear today global highscore memory
	for(i=0; i<MAX_TODAY_HIGHSCORE; i++)
	{
		todayHighScore[i].score=0;
		todayHighScore[i].level=0;
		todayHighScore[i].localTime=0;
		todayHighScore[i].name[0]=0x00;
		todayHighScore[i].location[0]=0x00;
	} 
	traceEvent(s_fn,0,"leave [void]");
}


/** 
 * Init Global highscore
 * 
 * @author wplaat
 */
void initGlobalHighScore(void)
{
	char *s_fn="initGlobalHighScore";
	traceEvent(s_fn,0,"enter");
	
	int i;   

	// Clear global highscore memory
	for(i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
	{
		globalHighScore[i].score=0;
		globalHighScore[i].level=0;
		globalHighScore[i].localTime=0;
		globalHighScore[i].name[0]=0x00;
		globalHighScore[i].location[0]=0x00;
	} 
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Init Game parameters
 *
 * @author wplaat
 */
void initGame()
{
   char *s_fn="initGame";
	int i;
	
   traceEvent(s_fn,0,"enter");
	
   // Init variables
   game.localTime=time(NULL);
	for (i=0; i<MAX_PLAYERS; i++)
	{
		players[i].score=0;  
		players[i].redsquare=-1;
	}
	
   game.prevPlayTime=0;
   game.speed=1;
	game.rating=1000;
	
	switch (settings.gameLevel)
	{
		case GAME_LEVEL_EASY: 
			game.borderSize=20;
			game.amountOfBlueSquares=3;
			break;
			
		case GAME_LEVEL_MEDIUM: 
			game.borderSize=40;
			game.amountOfBlueSquares=4;
			break;
			
		case GAME_LEVEL_HARD: 
			game.borderSize=60;
			game.amountOfBlueSquares=4;
			break;
	}
	
	selected1=false;
	selected2=false;
	   
	angle=0; 
   size=0;
   notesStartLine=1;
   
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Initiase red squares.
 * 
 * @author wplaat
 */
void initRedSquares(void)
{
	char *s_fn="initRedSquares";
   traceEvent(s_fn,0,"enter");

   // Red Square 1
   redSquares[0].image=images.redsquare;
   redSquares[0].width=redSquares[0].image->w;
   redSquares[0].height=redSquares[0].image->h;
	if (settings.players==1)
	{
		redSquares[0].x=(MAX_HORZ_PIXELS/2)-(redSquares[0].width/2);
		redSquares[0].y=(MAX_VERT_PIXELS/2)-(redSquares[0].height/2);
	}
	else
	{
		redSquares[0].x=(MAX_HORZ_PIXELS/2)-redSquares[0].width;
		redSquares[0].y=(MAX_VERT_PIXELS/2)-redSquares[0].height;
	}
	redSquares[0].visible=false;
	redSquares[0].player=-1;
	
	// Red Square 2
   redSquares[1].image=images.redsquare;
   redSquares[1].width=redSquares[1].image->w;
   redSquares[1].height=redSquares[1].image->h;
   redSquares[1].x=(MAX_HORZ_PIXELS/2)+redSquares[1].width;
   redSquares[1].y=(MAX_VERT_PIXELS/2)-redSquares[1].height;
	redSquares[1].visible=false;
	redSquares[1].player=-1;

	// Red Square 3
   redSquares[2].image=images.redsquare;
   redSquares[2].width=redSquares[2].image->w;
   redSquares[2].height=redSquares[2].image->h;
   redSquares[2].x=(MAX_HORZ_PIXELS/2)-redSquares[2].width;
   redSquares[2].y=(MAX_VERT_PIXELS/2)+redSquares[2].height;
	redSquares[2].visible=false;
	redSquares[2].player=-1;
	
	// Red Square 4
   redSquares[3].image=images.redsquare;
	redSquares[3].width=redSquares[3].image->w;
   redSquares[3].height=redSquares[3].image->h;
   redSquares[3].x=(MAX_HORZ_PIXELS/2)+redSquares[3].width;
   redSquares[3].y=(MAX_VERT_PIXELS/2)+redSquares[3].height;
	redSquares[3].visible=false;
	redSquares[3].player=-1;
	
	// Enable one redSquare per active player.
	int i;
	for (i=0; i<settings.players; i++)
	{
		redSquares[i].visible=true;
	}
	traceEvent(s_fn,0,"leave [void]");
}
	
/**
 * Initiase blue squares.
 * 
 * @author wplaat
 */
void initBlueSquares(void)
{
	char *s_fn="initBlueSquares";
   traceEvent(s_fn,0,"enter");

   int x, y;
	srand(time(NULL));
   
	// Blue Square 1
	if (settings.randomPositions==RANDOM_START_POS_NO)
	{
	   x=10;
		y=10;
	} 
	else 
	{
		x=10+((int) (rand() % 200));
		y=10;
	}
   blueSquares[0].image=images.bluesquare1;
	blueSquares[0].width=blueSquares[0].image->w;
   blueSquares[0].height=blueSquares[0].image->h;
   blueSquares[0].x=x;
   blueSquares[0].y=y;
   blueSquares[0].directionX=true;
   blueSquares[0].directionY=true;
	blueSquares[0].visible=true;
	
   // Blue Square 2
	if (settings.randomPositions==RANDOM_START_POS_NO)
	{
	   x=MAX_HORZ_PIXELS-blueSquares[1].width-10;
		y=10;
	} 
	else 
	{
		x=MAX_HORZ_PIXELS-blueSquares[1].width-10-((int) (rand() % 200));
		y=10;
	}
   blueSquares[1].image=images.bluesquare2;
	blueSquares[1].width=blueSquares[1].image->w;
   blueSquares[1].height=blueSquares[1].image->h;
   blueSquares[1].x=x;
   blueSquares[1].y=y;
   blueSquares[1].directionX=false;
   blueSquares[1].directionY=true;
	blueSquares[1].visible=true;
      
   // Blue Square 3
   if (settings.randomPositions==RANDOM_START_POS_NO)
	{
	   x=10;
		y=MAX_VERT_PIXELS-blueSquares[2].height-10;
	} 
	else 
	{
		x=10+((int) (rand() % 200));
		y=MAX_VERT_PIXELS-blueSquares[2].height-10;
	}
	blueSquares[2].image=images.bluesquare3;
	blueSquares[2].width=blueSquares[2].image->w;
   blueSquares[2].height=blueSquares[2].image->h;
   blueSquares[2].x=x;
   blueSquares[2].y=y;
   blueSquares[2].directionX=true;
   blueSquares[2].directionY=false;
	blueSquares[2].visible=true;
      
   // Blue Square 4
	if (settings.randomPositions==RANDOM_START_POS_NO)
	{
	   x=MAX_HORZ_PIXELS-blueSquares[3].width-10;
		y=MAX_VERT_PIXELS-blueSquares[3].height-10;
	} 
	else 
	{
		x=MAX_HORZ_PIXELS-blueSquares[3].width-10-((int) (rand() % 200));
		y=MAX_VERT_PIXELS-blueSquares[3].height-10;
	}
   blueSquares[3].image=images.bluesquare4;
	blueSquares[3].width=blueSquares[3].image->w;
   blueSquares[3].height=blueSquares[3].image->h;
   blueSquares[3].x=x;
   blueSquares[3].y=y;   
   blueSquares[3].directionX=false;
   blueSquares[3].directionY=false;
	blueSquares[3].visible=true;
   
   traceEvent(s_fn,0,"leave [void]");
}

/** 
 * Detect with player had the highest score
 * 
 * @author wplaat
 *
 * @return highest score
 */
int highestScore()
{
	char *s_fn="highestScore";
   traceEvent(s_fn,0,"enter");
	
	int i; 
	int score=0;
	
	for(i=0; i<settings.players; i++)
	{
		if (score<players[i].score)
		{
			score=players[i].score;
		}
	}
	
	traceEvent(s_fn,0,"leave [score=%d]",score);
	return score;
}

/**
 * Find best Player
 *
 * @author wplaat
 *
 * @return player number.
 */
int bestPlayer()
{
	char *s_fn="highestScore";
   traceEvent(s_fn,0,"enter");
	
	int i; 
	int score=0;
	int nr=0;
	
	for(i=0; i<settings.players; i++)
	{
		if (score<players[i].score)
		{
			score=players[i].score;
			nr=i;
		}
	}
	
	traceEvent(s_fn,0,"leave [nr=%d]",nr);
	return nr;
}
	
// -----------------------------------------------------------
// Highscore methods
// -----------------------------------------------------------

/**
 * Save Local highscore to SDcard.
 * 
 * @author wplaat
 * 
 * @param filename	The filename
 */
void saveLocalHighScoreFile(char* filename)
{
   char *s_fn="saveLocalHighScoreFile";
   traceEvent(s_fn,0,"enter");
   
	int selectedHighScore=0;
   int i;
   bool store=false;
   mxml_node_t *xml;
   mxml_node_t *group;
   mxml_node_t *data;   
   char tmp[MAX_LEN];
	
	// Get high score of last game
	int score=highestScore();
      
   xml = mxmlNewXML("1.0");
   group = mxmlNewElement(xml, "RedSquare");
   
   for(i=0; i<MAX_LOCAL_HIGHSCORE; i++)
   {
      if ((score>=highscores[i].score) && !store)
	   {
			sprintf(tmp, "entry%d", i);
         data = mxmlNewElement(group, tmp);
  
			sprintf(tmp, "%d", (int) game.localTime);
         mxmlElementSetAttr(data, "localTime", tmp);
	  
			sprintf(tmp, "%d", (int) score);
			mxmlElementSetAttr(data, "playTime", tmp);
		 
		   sprintf(tmp, "%d", (int) settings.gameLevel);
			mxmlElementSetAttr(data, "level", tmp);
			
			mxmlElementSetAttr(data, "name", settings.name);
			
			game.rating=i;
			store=true;
	  }
	  else
	  {	  
			sprintf(tmp, "entry%d", i);
			data = mxmlNewElement(group, tmp);
  
			sprintf(tmp, "%d", (int) highscores[selectedHighScore].localTime);
			mxmlElementSetAttr(data, "localTime", tmp);
	  
			sprintf(tmp, "%d", (int) highscores[selectedHighScore].score);
			mxmlElementSetAttr(data, "playTime", tmp);
		
		   sprintf(tmp, "%d", (int) highscores[selectedHighScore].level);
			mxmlElementSetAttr(data, "level", tmp);
			
			mxmlElementSetAttr(data, "name", highscores[selectedHighScore].name);

			selectedHighScore++;		
	   }	  
   }
  
   /* now lets save the xml file to a file! */
   FILE *fp;
   fp = fopen(filename, "w");

   mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
   /*Time to clean up!*/
   fclose(fp);
   mxmlDelete(data);
   mxmlDelete(group);
   mxmlDelete(xml);
   
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Load Today highscore 
 * 
 * @author wplaat
 * 
 * @param buffer	The xml data received from internet
 */
void loadTodayHighScore(char *buffer)
{
   char *s_fn="loadTodayHighScore";
   traceEvent(s_fn,0,"enter");
   
   int i;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
   
   maxTodayHighScore=0;
   
   // Clear memory
   for(i=0; i<MAX_TODAY_HIGHSCORE; i++)
   {
      todayHighScore[i].score=0;
		todayHighScore[i].level=0;
		todayHighScore[i].localTime=0;
		todayHighScore[i].name[0]=0x00;
		todayHighScore[i].location[0]=0x00;
   } 
	 
   // If xml data available, parse it....
   if ((buffer!=NULL) && (strlen(buffer)>0))
   {  
      tree = mxmlLoadString(NULL, buffer, MXML_NO_CALLBACK);

      for(i=0; i<MAX_TODAY_HIGHSCORE; i++)
      {		
			sprintf(temp, "item%d", i+1);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);

			tmp=mxmlElementGetAttr(data,"dt");   
			if (tmp!=NULL) 
			{	
				todayHighScore[maxTodayHighScore].localTime=atoi(tmp); 
			}
			else 
			{
				todayHighScore[maxTodayHighScore].localTime=0; 
			}
		
			tmp=mxmlElementGetAttr(data,"score");   
			if (tmp!=NULL) 
			{
				todayHighScore[maxTodayHighScore].score=atoi(tmp); 
			}
			else 
			{
				todayHighScore[maxTodayHighScore].score=0;
			}
			
			tmp=mxmlElementGetAttr(data,"level");   
			if (tmp!=NULL) 
			{
				todayHighScore[maxTodayHighScore].level=atoi(tmp); 
			}
			else 
			{
				todayHighScore[maxTodayHighScore].level=0;
			}
		
			tmp=mxmlElementGetAttr(data,"name");   
			if (tmp!=NULL) strcpy(todayHighScore[maxTodayHighScore].name,tmp); 
				else strcpy(todayHighScore[maxTodayHighScore].name,"");

			tmp=mxmlElementGetAttr(data,"location");   
			if (tmp!=NULL) strcpy(todayHighScore[maxTodayHighScore].location,tmp);
				else strcpy(todayHighScore[maxTodayHighScore].location,"");
		
			// Entry is valid (Keep the information)
			if (todayHighScore[maxTodayHighScore].score>0) maxTodayHighScore++;	
      }   
      mxmlDelete(data);
      mxmlDelete(tree);
   }
   
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Load Global highscore 
 *
 * @author wplaat
 *
 * @param buffer	The xml data received from internet
 */
void loadGlobalHighScore(char *buffer)
{
   char *s_fn="loadGlobalHighScore";
   traceEvent(s_fn,0,"enter");
   
   int i;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
   
   maxGlobalHighScore=0;
   
   // Clear memory
   for(i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
   {
      globalHighScore[i].score=0;
		globalHighScore[i].localTime=0;
		globalHighScore[i].name[0]=0x00;
		globalHighScore[i].location[0]=0x00;
   } 
	 
   // If xml data available, parse it....
   if ((buffer!=NULL) && (strlen(buffer)>0))
   {  
      tree = mxmlLoadString(NULL, buffer, MXML_NO_CALLBACK);

      for(i=0; i<MAX_GLOBAL_HIGHSCORE; i++)
      {		
			sprintf(temp, "item%d", i+1);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);

			tmp=mxmlElementGetAttr(data,"dt");   
			if (tmp!=NULL) 
			{
				globalHighScore[maxGlobalHighScore].localTime=atoi(tmp); 
			}
			else 
			{
				globalHighScore[maxGlobalHighScore].localTime=0; 
			}
		
			tmp=mxmlElementGetAttr(data,"score");   
			if (tmp!=NULL) 
			{
				globalHighScore[maxGlobalHighScore].score=atoi(tmp); 
			}
			else 
			{
				globalHighScore[maxGlobalHighScore].score=0;
			}
		
			tmp=mxmlElementGetAttr(data,"level");   
			if (tmp!=NULL) 
			{
				globalHighScore[maxGlobalHighScore].level=atoi(tmp); 
			}
			else 
			{
				globalHighScore[maxGlobalHighScore].level=0;
			}
			
			tmp=mxmlElementGetAttr(data,"name");   
			if (tmp!=NULL) 
			{
				strcpy(globalHighScore[maxGlobalHighScore].name,tmp); 
			}
			else 
			{
				strcpy(globalHighScore[maxGlobalHighScore].name,"");
			}

			tmp=mxmlElementGetAttr(data,"location");   
			if (tmp!=NULL) 
			{
				strcpy(globalHighScore[maxGlobalHighScore].location,tmp);
			} 
			else 
			{
				strcpy(globalHighScore[maxGlobalHighScore].location,"");
			}
		
			// Entry is valid (Keep the information)
			if (globalHighScore[maxGlobalHighScore].score>0) maxGlobalHighScore++;	
      }   
      mxmlDelete(data);
      mxmlDelete(tree);
   }
   
   traceEvent(s_fn,0,"leave [void]");
}

/**
 * Load Local highscore 
 *
 * @author wplaat
 *
 * @param filename	The filename with xml highscore data
 */
void loadLocalHighScoreFile(char* filename)
{
   char *s_fn="loadLocalHighScoreFile";
   traceEvent(s_fn,0,"enter");
   
   int i;
   FILE *fp;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   char temp[MAX_LEN];
   
   maxLocalHighScore=0;

   /*Load our xml file! */
   fp = fopen(filename, "r");
   if (fp!=NULL)
   {
		tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
		fclose(fp);

		traceEvent(s_fn,0,"Parse Local highscore xml file.");

		for(i=0; i<MAX_LOCAL_HIGHSCORE; i++)
		{
			sprintf(temp, "entry%d", i);
			data = mxmlFindElement(tree, tree, temp, NULL, NULL, MXML_DESCEND);
  
			tmp=mxmlElementGetAttr(data,"localTime");   
			if (tmp!=NULL) 
			{
				highscores[maxLocalHighScore].localTime=atoi(tmp); 
			}
			else 
			{
				highscores[maxLocalHighScore].localTime=0;
			}
		
			tmp=mxmlElementGetAttr(data,"playTime"); 
			if (tmp!=NULL) 
			{
				highscores[maxLocalHighScore].score=atoi(tmp); 
			}
			else 
			{
				highscores[maxLocalHighScore].score=0;
			}
		
			tmp=mxmlElementGetAttr(data,"level"); 
			if (tmp!=NULL) 
			{
				highscores[maxLocalHighScore].level=atoi(tmp); 
			}
			else 
			{
				highscores[maxLocalHighScore].level=0;
			}
			
			tmp=mxmlElementGetAttr(data,"name"); 
			if (tmp!=NULL)
			{ 
				strcpy(highscores[maxLocalHighScore].name,tmp); 
			}
			else 
			{
				strcpy(highscores[maxLocalHighScore].name,"");
			}
		
			// Entry is valid (Keep the inforamtion)
			if (highscores[maxLocalHighScore].localTime>0) 
			{
				maxLocalHighScore++;		
			}
		} 
   }
   else
   {
		traceEvent(s_fn,0,"Local highscore file note found!");
	
		// If file not found, create empty highscore list.
		for(i=0; i<MAX_LOCAL_HIGHSCORE; i++)
		{
			highscores[i].localTime=0;
			highscores[i].score=0;
			highscores[i].level=0;
			memset(highscores[i].name,0x00,MAX_LEN);
		} 
   }
   
   mxmlDelete(data);
   mxmlDelete(tree);
   
   traceEvent(s_fn,0,"leave [void]");
}

// -----------------------------------------------------------
// Game support methods
// -----------------------------------------------------------

/**
 * Move square
 *
 * @author wplaat
 *
 * @param amount	The amount of active blue squares.
 */
void moveBlueSquares(int amount)
{ 
	//char *s_fn="moveBlueSquares";
   //traceEvent(s_fn,0,"enter");
	
   int i;
   
   for (i=0; i<amount; i++)
   {
      if (blueSquares[i].directionX)
	   {
         if (blueSquares[i].x+blueSquares[i].width<MAX_HORZ_PIXELS)
	      {
	         blueSquares[i].x=blueSquares[i].x+game.speed;	   
	      }
	      else
	      {
	         blueSquares[i].directionX=false;
		      blueSquares[i].x=blueSquares[i].x-game.speed;	
				if (stateMachine==stateGame) 
				{
					SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 
						8000, 0, (u8 *) effect1_pcm, effect1_pcm_size, 
						settings.effectVolume*EFFECT_MULTIPLER, 
						settings.effectVolume*EFFECT_MULTIPLER, NULL);
				}
	      }	
	   }
      else  	   
	   {
	      if (blueSquares[i].x<=0)
	      {
	         blueSquares[i].directionX=true;
		      blueSquares[i].x=blueSquares[i].x+game.speed;	
			   if (stateMachine==stateGame) 
				{	
					SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 
						8000, 0, (u8 *) effect1_pcm, effect1_pcm_size, 
						settings.effectVolume*EFFECT_MULTIPLER, 
						settings.effectVolume*EFFECT_MULTIPLER, NULL);
				}
		   }
		   else
		   {
		      blueSquares[i].x=blueSquares[i].x-game.speed;	
		   }
	   }
	   
	   if (blueSquares[i].directionY)
	   {
         if (blueSquares[i].y+blueSquares[i].height<MAX_VERT_PIXELS)
	      {
	          blueSquares[i].y=blueSquares[i].y+game.speed;	   
	      }
	      else
	      {
	         blueSquares[i].directionY=false;
		      blueSquares[i].y=blueSquares[i].y-game.speed;	
				if (stateMachine==stateGame) 
				{
					SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 
						8000, 0, (u8 *) effect1_pcm, effect1_pcm_size, 
						settings.effectVolume*EFFECT_MULTIPLER, 
						settings.effectVolume*EFFECT_MULTIPLER, NULL);
				}
	      }	
	   }
      else  	   
	   {
	      if (blueSquares[i].y<=0)
	      {
	         blueSquares[i].directionY=true;
		      blueSquares[i].y=blueSquares[i].y+game.speed;	
				if (stateMachine==stateGame) 
				{	
					SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000,
						0, (u8 *) effect1_pcm, effect1_pcm_size, 
						settings.effectVolume*EFFECT_MULTIPLER, 
						settings.effectVolume*EFFECT_MULTIPLER, NULL);
				}
		   }
		   else
		   {
		      blueSquares[i].y=blueSquares[i].y-game.speed;	
		   }
	   }
   }
	//traceEvent(s_fn,0,"leave [void]");
}

/**
 * Move redSquares
 *
 * @author wplaat
 */
void moveRedSquares(void)
{
	//char *s_fn="moveRedSquares";
   //traceEvent(s_fn,0,"enter");
	
	int i=0;
	for (i=0; i<MAX_RED_SQUARES; i++)
	{
		if ((redSquares[i].visible) && (redSquares[i].player!=-1))
		{
			redSquares[i].x=pointers[redSquares[i].player].xOffset-40;
			redSquares[i].y=pointers[redSquares[i].player].yOffset-40;
		}
	}
	//traceEvent(s_fn,0,"leave [void]");
}

/**
 * Check for collision between blue and red square and the walls.
 *
 * @author wplaat
 *
 * @param nr	The number of a red square.
 *
 * @return if collision the true else false.
 */
bool collisionDetection(int nr)
{
	//char *s_fn="collisionDetection";
   //traceEvent(s_fn,0,"enter");
	
   int i,x,y;
	bool collision = false;
	  	 
	// Wall collision detection
   if (redSquares[nr].x<=game.borderSize)
	{
	    collision = true;       	 
	}
	 
	if (redSquares[nr].x+redSquares[nr].width>MAX_HORZ_PIXELS-game.borderSize)
	{
	   collision = true; 	 
	}
	 
	if (redSquares[nr].y<=game.borderSize)
	{
		collision = true;      	 
	}
	 
   if (redSquares[nr].y+redSquares[nr].height>=MAX_VERT_PIXELS-game.borderSize)
	{
		collision = true;     	 
	}
	 	 
	// blue square collesion detection
	for (i=0; i<game.amountOfBlueSquares; i++)
	{ 		
	   for (x=blueSquares[i].x; x<blueSquares[i].x+blueSquares[i].width; x++)
		{
	      if (x>=redSquares[nr].x) 
		   {
		      if (x<=redSquares[nr].x+redSquares[nr].width)			
            {			  
			      if (blueSquares[i].y>=redSquares[nr].y) 
			      {
						if (blueSquares[i].y<=redSquares[nr].y+redSquares[nr].height)
						{
							collision = true; 		 
						}
			      }
 
			      if (blueSquares[i].y+blueSquares[i].height>=redSquares[nr].y) 
			      {
						if (blueSquares[i].y+blueSquares[i].height<=redSquares[nr].y+redSquares[nr].height)
						{
							collision = true; 	 
						}
				  }
			   }
			}			
		 }
		 				 
       for (y=blueSquares[i].y; y<blueSquares[i].y+blueSquares[i].height; y++)						 
		 {
   	   if (y>=redSquares[nr].y) 
			{
			   if (y<=redSquares[nr].y+redSquares[nr].height)
			   {
			   	if (blueSquares[i].x>=redSquares[nr].x) 
		         {
		            if (blueSquares[i].x<=redSquares[nr].x+redSquares[nr].width)			
                  { 	
							collision = true; 	 
						}
					}
					if (blueSquares[i].x+blueSquares[i].width>=redSquares[nr].x) 
					{
		            if (blueSquares[i].x+blueSquares[i].width<=redSquares[nr].x+redSquares[nr].width)			
                  { 	
							collision = true; 		 
						}
					}
			   }
			}
		 }		
	 }
	 
	 // traceEvent(s_fn,0,"leave [%d]",collision);
	 return collision;
}

/**
 * Detect if game is over. All players have collisioned
 *
 * @author wplaat
 * 
 * @return Gameover (true or false)
 */
bool detectGameOver()
{
	//char *s_fn="detectGameOver";
   //traceEvent(s_fn,0,"enter");
	
   int i;
	bool gameOver=true;
	
   for (i=0; i<MAX_RED_SQUARES; i++)
	{
		if (redSquares[i].visible) 
		{
			gameOver=false;
			break;
		}
	}
	
	//traceEvent(s_fn,0,"leave [gameOver=%d]",gameOver);
	return gameOver;
}


/**
 * Process actions during game play. 
 *
 * @author wplaat
 */
void processGameEvents()
{ 		 
	char *s_fn="processGameEvents";
   //traceEvent(s_fn,0,"enter");
	
   int i,j;
	
	// By single player start score direct
	if (settings.players==1)
	{
		players[0].score++;
	}
	else
	{
	   /// By multi players start score after redsquare is selected
		for (i=0; i<settings.players; i++)
		{
			for (j=0; j<MAX_RED_SQUARES; j++)
			{
				if ((redSquares[j].player==i) && (redSquares[j].visible))
				{
					players[i].score++;
					break;
				}
			}
		}
	}
	
	// Every 10 seconds the blue squares accelarate with one pixel size.
	game.playTime = time(NULL)-game.localTime;   
	if (game.prevPlayTime!=game.playTime)
	{
	   if ((game.playTime % 10)==0) 
		{
		   game.speed++;			  
	      game.prevPlayTime=game.playTime;
			traceEvent(s_fn,0,"Speed up [%d] blue movement", game.prevPlayTime );
		}
	}
		
	for (i=0; i<MAX_RED_SQUARES; i++)
	{
		if ((redSquares[i].visible) && (collisionDetection(i)))
		{				
			traceEvent(s_fn,0,"RedSquare [%d] died", i);

			SND_SetVoice(SND_GetFirstUnusedVoice(), 
				VOICE_MONO_8BIT, 
				8000, 
				0, 
				(u8 *) effect2_pcm, 
				effect2_pcm_size, 
				settings.effectVolume*EFFECT_MULTIPLER, 
				settings.effectVolume*EFFECT_MULTIPLER, 
				NULL);
				
			redSquares[i].visible=false;
		}
	}

	if (detectGameOver())
	{
		traceEvent(s_fn,0,"Game over!");
		
		stateMachine=stateGameOver;
		
		// Save score to highscore list
		saveLocalHighScoreFile(HIGHSCORE_FILENAME);
		loadLocalHighScoreFile(HIGHSCORE_FILENAME);	
	  
	   // If top 5 rating play sound!
	   if (game.rating<5)
		{
		  SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 22050, 
				0, (char *) topscore_pcm, topscore_pcm_size, 
				settings.effectVolume*EFFECT_MULTIPLER,
				settings.effectVolume*EFFECT_MULTIPLER, NULL);
		}
		
      // Sent score to webservice.
		if (highestScore()>=MIN_SCORE)
		{
		   int map=0; // USA Mode
		   if (yOffset>0) map=1; // Europa Mode
			  
		   sprintf(appl_user3,"appl=%s&version=%s&level=%d&score=%d&name=%s&dt=%d&map=%d",
				PROGRAM_NAME,
				PROGRAM_VERSION,
				settings.gameLevel,
				highestScore(),
				settings.name,
				(int)game.localTime,
				map );
						
		   tcp_set_state(TCP_REQUEST3a, appl_user3);			  
		}
	}		   		  
	//traceEvent(s_fn,0,"leave [void]");
}

// -----------------------------------------------------------
// BUTTON LOGIC
// -----------------------------------------------------------

/**
 * button Selected
 *
 * @author wplaat
 *
 * @param x 		The x position of the WiiMote.
 * @param y 		The y position of the WiiMote.
 * @param sound 	The sound flag
 */ 
int buttonSelected(int x, int y, bool sound)
{
	char *s_fn="buttonSelected";
   traceEvent(s_fn,0,"enter");
	
	int nr=-1;
   int i;
   
   for (i=0; i<maxButtons; i++)
   {
      if ( 	(x>=buttons[i].x) && 
				(x<=buttons[i].x+buttons[i].image->w) && 
				(y>=buttons[i].y) && 
				(y<=buttons[i].y+buttons[i].image->h) )
	   {
			if (sound)
			{
				SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 
					22050, 0, (char *) effect3_pcm, effect3_pcm_size, 
					settings.effectVolume*EFFECT_MULTIPLER, 
					settings.effectVolume*EFFECT_MULTIPLER, NULL);
			}
	      nr=i;
			break;
	   }	   
   }
	traceEvent(s_fn,0,"leave [nr=%d]",nr);
   return nr;
}

/**
 * process button scroll event
 *
 * @author wplaat
 *
 * @param index	The pointer index number.
 */ 
void buttonScroll(int index )
{ 
	char *s_fn="buttonScroll";
   
	switch (stateMachine)
	{
		case stateLocalHighScore:
		case stateTodayHighScore:
		case stateGlobalHighScore:
		case stateReleaseNotes:
		{ 
			traceEvent(s_fn,0,"enter [index=%d]", index);
    
			int x = pointers[index].xOffset;
			int y = pointers[index].yOffset;
					
			switch (buttonSelected(x,y,false))
			{
				case 1: 	if ((y-40)>SCROLLBAR_Y_MIN && (y-40)<SCROLLBAR_Y_MAX) 
							{
								buttons[1].y=y-40;	
								scrollIndex=(buttons[1].y-SCROLLBAR_Y_MIN)/6;
							}
							break;	  
			}
			
			traceEvent(s_fn,0,"leave [void]");
		}
	}
}

/**
 * Process 1 or X button event
 *
 * @author wplaat
 *
 * @param index	The WiiMote index number.
 */
void button1x(int index)
{
	char *s_fn="button1x";
   traceEvent(s_fn,0,"enter [index=%d]",index);
	
   if (selected1) return;

	selected1=true;
		
   MODPlay_Stop(&snd1);  
   if (selectedMusic<MAX_MUSIC_TRACK) 
	{
		selectedMusic++; 
	}
	else 
	{
		selectedMusic=1;   
	}
   initMusicTrack();       
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Process 2 or Y button event
 *
 * @author wplaat
 *
 * @param index	The WiiMote index number.
 */
void button2y(int index)
{
	char *s_fn="button2y";
   traceEvent(s_fn,0,"enter [index=%d]", index);
	
   if (selected2) return;
   selected2=true;   
   
	MODPlay_Stop(&snd1);
   if (selectedMusic>1) 
	{
		selectedMusic--; 
	}
	else 
	{
		selectedMusic=MAX_MUSIC_TRACK;   
	}
	
   initMusicTrack();
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Process minus button event
 *
 * @author wplaat
 *
 * @param index	The event index number
 */
void buttonMinus(int index)
{
	char *s_fn="buttonMinus";
   traceEvent(s_fn,0,"enter");
	
   switch (index)   
   {
       case 0:
	      // Music volume
	      if (settings.musicVolume>0) settings.musicVolume--;   
	      MODPlay_SetVolume( &snd1, 
				settings.musicVolume*MUSIC_MULTIPLER,
				settings.musicVolume*MUSIC_MULTIPLER);
		  break;
       
	   case 1:
          // Effect volume
          if (settings.effectVolume>0) 
			 {
				settings.effectVolume--; 
			 }
		    break;
   
       case 2:
	      // Prev music track
          MODPlay_Stop(&snd1);
          if (selectedMusic>1) selectedMusic--; else selectedMusic=MAX_MUSIC_TRACK;
	      initMusicTrack();
		  break;
	
	    case 3:
		  // First Character
		  settings.name[0]=getLetter(settings.name[0],false);
		  break;
		  
		case 4:
		  // Second Character
		  settings.name[1]=getLetter(settings.name[1],false);
		  break;
		  
		case 5:
		  // Third Character
		  settings.name[2]=getLetter(settings.name[2],false);
		  break;
		  
		case 6:
		  // Third Character
		  settings.name[3]=getLetter(settings.name[3],false);
		  break;
		  
		case 7:
		  // Fifth Character
		  settings.name[4]=getLetter(settings.name[4],false);
		  break;
		  
		case 8:
		  // Sixth Character
		  settings.name[5]=getLetter(settings.name[5],false);
		  break;
   }
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Process plus button event
 *
 * @author wplaat
 *
 * @param index	The event index number
 */
void buttonPlus(int index)
{
	char *s_fn="buttonPlus";
   traceEvent(s_fn,0,"enter");
		
   switch (index)
   {
      case 0:
         // Music volume
	     if (settings.musicVolume<MAX_SOUND_VOLUME) settings.musicVolume++;   
	     MODPlay_SetVolume( &snd1, 
				settings.musicVolume*MUSIC_MULTIPLER,
				settings.musicVolume*MUSIC_MULTIPLER); 
		 break;
		 
	  case 1:
         // Effect volume
         if (settings.effectVolume<MAX_SOUND_VOLUME) 
			{
				settings.effectVolume++; 
			}
		 break;
		 
	  case 2:
	     // Next music Track
         MODPlay_Stop(&snd1);
         if (selectedMusic<MAX_MUSIC_TRACK) 
			{
				selectedMusic++; 
			}
			else 
			{
				selectedMusic=1;
			}
	      initMusicTrack();
		   break;
		 
	  case 3:
		  // First Character
		  settings.name[0]=getLetter(settings.name[0],true);
		  break;
		  
	  case 4:
		  // Second Character
		  settings.name[1]=getLetter(settings.name[1],true);	
		  break;
		  
	  case 5:
		  // Third Character
		  settings.name[2]=getLetter(settings.name[2],true);		
		  break;

	  case 6:
		  // Fourth Character
		  settings.name[3]=getLetter(settings.name[3],true);
		  break;
		  
	  case 7:
		  // Fifth Character
		  settings.name[4]=getLetter(settings.name[4],true);	
		  break;
		  
	  case 8:
		  // Sixth Character
		  settings.name[5]=getLetter(settings.name[5],true);		
		  break;
		  
		  // Make a screenshot including wiimote pointers.
	  case 9: 
			{
				char filename[MAX_LEN];
				struct tm *level;	   
				time_t dt=time(NULL);
				level = localtime(&dt);
				sprintf(filename,"%sRedSquare-%04d%02d%02d%02d%02d%02d.png", GAME_DIRECTORY, level->tm_year+1900,level->tm_mon+1, level->tm_mday,  level->tm_hour, level->tm_min, level->tm_sec);		  
				GRRLIB_ScrShot(filename);
			}
			break;
   }
	traceEvent(s_fn,0,"leave [void]");
}

int redSquareSelected(int x, int y)
{
   char *s_fn="redSquareSelected";
   traceEvent(s_fn,0,"enter [x=%d, y=%d]",x,y);
	
	int nr=-1;
	int i;
   for (i=0; i<MAX_RED_SQUARES; i++)
   {
		traceEvent(s_fn,0,"redsquare [id=%d,x=%d,y=%d,width=%d,height=%d]"
				,i,
				redSquares[i].x,
				redSquares[i].y,
				redSquares[i].width,
				redSquares[i].height );
	
      if ( 	(redSquares[i].visible) &&
				(x >= redSquares[i].x ) && 
				(x <= (redSquares[i].x+redSquares[i].width)) && 
				(y >= redSquares[i].y) && 
				(y <= (redSquares[i].y+redSquares[i].height)) &&
				(redSquares[i].player==-1) )
	   {
	      nr=i;
			break;
	   }	   
   }
	
	traceEvent(s_fn,0,"leave [nr=%d]",nr);
   return nr;
}

/**
 * Process B button event
 *
 * @author wplaat
 *
 * @param index	The index number of the WiiMote.
 */
void buttonB(int index)
{
	char *s_fn="buttonB";
   traceEvent(s_fn,0,"enter [index=%d]",index);
	
	// If player has not redsquare yet, continuee..
	if ((stateMachine==stateGame) && (players[index].redsquare==-1))
	{
		int nr = redSquareSelected(
				pointers[index].xOffset,
				pointers[index].yOffset);
		if ( nr != -1)
		{
			redSquares[nr].player=index;
			players[index].redsquare=nr;
		}
	}
	traceEvent(s_fn,0,"leave [void]");
}

/**
 * Process A button event
 *
 * @author wplaat
 *
 * @param index 	The index of the WiiMote.
 */
void buttonA(int index)
{ 
	char *s_fn="buttonA";
   traceEvent(s_fn,0,"enter [index=%d]",index);
	
	int x = pointers[index].xOffset;
	int y = pointers[index].yOffset;
					
   switch (stateMachine)
   {
		case stateIntro1:
		{
			size=0;
			stateMachine=stateIntro2;
		}
		break;

		case stateIntro2:
		{
			stateMachine=stateIntro3;
		}
		break;
	 
		case stateIntro3:
		{
			stateMachine=stateIntro4;
		}
		break;
	 
		case stateIntro4:
		{
			stateMachine=stateMenu;
		}
		break;
		
		case stateMenu:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: // play button	
					initBlueSquares();
					initRedSquares();
               initGame();  		
					stateMachine=stateGame;		
					WPAD_Rumble(0,0);		  
			      break;
	  
				case 1: // High Score button 
					scrollIndex=0;
					stateMachine=stateLocalHighScore;
			      break;
				  
				case 2: // Help button 
					stateMachine=stateHelp1;
			      break;
	  
				case 3: // Credits button 		 
					stateMachine=stateCredits;
			      break;
		  
				case 4: // Sound button 		 
					stateMachine=stateSoundSettings;
			      break;
				  
				case 5: // Release Notes button 		 
					scrollIndex=0;
					stateMachine=stateReleaseNotes;
			      break;
				  
				case 6: // Games Settings button 		 
					stateMachine=stateGameSettings;
			      break;
				  
				case 7: // Donate button 		 
					stateMachine=stateDonate;
			      break;
					
				case 8: // Exit HBC button 
			      stateMachine=stateQuit;
			      break;	
				  
				case 9: // Reset Wii button 
					SYS_ResetSystem(SYS_RESTART,0,0);
			      break; 
			}
		}
		break;

		case stateGame:
			// If player has not redsquare yet, continuee..
			if ( (stateMachine==stateGame) && 
				  (players[index].redsquare==-1) )
			{
				int nr = redSquareSelected(
					pointers[index].xOffset,
					pointers[index].yOffset);
					
				if ( nr != -1)
				{
					// Connect redsqaure to player
					redSquares[nr].player=index;
					players[index].redsquare=nr;
				}
			}
			break;
			
		case stateSoundSettings:
		{     
  	      switch (buttonSelected(x,y,true))
	      {
			 case 0: // - music volume button event	           
			         buttonMinus(0);
			         break;	   
			 
			 case 1: // + music volume button event	           
			         buttonPlus(0);
			         break;	 
					 
			 case 2: // - effect volume button event	           
			         buttonMinus(1);
			         break;	   
			 
			 case 3: // + effect volume button event	           
			         buttonPlus(1);
			         break;	 
					 
			 case 4: // - music track button event	           
			         buttonMinus(2);
			         break;	   
			 
			 case 5: // + music track  button event	           
			         buttonPlus(2);
			         break;
					 
			 case 6: // Back button event   
					{					  
					   saveSettingFile(SETTING_FILENAME);  
					   stateMachine=stateMenu;  
					}
			      break;	   				 
			}
		}
		break;

		case stateReleaseNotes:
		{     
  	      switch (buttonSelected(x,y,true))
	      {		
			 case 0: // Back button event          
			         stateMachine=stateMenu;
			         break;	   
		  }
		}
		break;
	 
		case stateGameOver:
		{
			// Go to menu screen when A is pressed
			stateMachine=stateMenu;
			initGame(); 
		}
		break;
	 
		case stateLocalHighScore:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: // Next button	
					scrollIndex=0;
					stateMachine=stateTodayHighScore;
					break;	     
			}
		}
		break;
	 
		case stateTodayHighScore:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: // Back button	
						scrollIndex=0;
						stateMachine=stateGlobalHighScore;
						break;	     
			}
		}
		break;
	 
		case stateGlobalHighScore:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: 	
					// Back button	
					stateMachine=stateMenu;
					break;	     
			}
		}
		break;
	 
		case stateHelp1:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: 	
					// Next button	
					stateMachine=stateHelp2;
					break;	     
			}
		}
		break;
	 
		case stateHelp2:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: 
					// Menu button	
					stateMachine=stateMenu;
					break;	     
			}
		}
		break;
	 
		case stateCredits:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: 
					// Next button	
					stateMachine=stateMenu;
					break;	     
			}
		}
		break;
	 
		case stateGameSettings:
		{     
			switch (buttonSelected(x,y,true))
			{
			case 0: // + First Character button event	           
			         buttonPlus(3);
			         break;	   
			 
			case 1: // - First Character button event	           
			         buttonMinus(3);
			         break;	 
					 
			case 2: // + Second Character button event           
			         buttonPlus(4);
			         break;	   
			 
			case 3: // - Second Character button event         
			         buttonMinus(4);
			         break;	 
					 
			case 4: // + Third Character button event         
			         buttonPlus(5);
			         break;	   
			 
			case 5: // - Third Character button event           
			         buttonMinus(5);
			         break;
			
			case 6: // + Fourth Character button event         
			         buttonPlus(6);
			         break;	   
			 
			case 7: // - Fourth Character button event           
			         buttonMinus(6);
			         break;
					 
			case 8: // + Fifth Character button event         
			         buttonPlus(7);
			         break;	   
			 
			case 9: // - Fifth Character button event           
			         buttonMinus(7);
			         break;
					 
			case 10: // + Sixth Character button event         
			         buttonPlus(8);
			         break;	   
			 
			case 11: // - Sixth Character button event           
			         buttonMinus(8);
			         break;

			case 12 :if (settings.players<MAX_POINTERS)
						{
							settings.players++;
						}
						else
						{
							settings.players=1;
						}
		
						// Refresh Buttons labels.
						initButtons();				
						break;
					
			case 13: if (settings.gameLevel<GAME_LEVEL_HARD) 
						{
						   settings.gameLevel++;
						} 
						else 
						{
							settings.gameLevel=GAME_LEVEL_EASY;
						}
						 
						// Refresh Buttons labels.
						initButtons();
						break;
		
			case 14: if (settings.randomPositions==RANDOM_START_POS_NO) 
						{
						   settings.randomPositions++;
						} 
						else 
						{
							settings.randomPositions=RANDOM_START_POS_NO;
						}
						 
						// Refresh Buttons labels.
						initButtons();			
						break;
	
			case 15: // Back button event      
						saveSettingFile(SETTING_FILENAME);    
			         stateMachine=stateMenu;
			         break;	   
			}
		}
		break;

		case stateDonate:
		{
			switch (buttonSelected(x,y,true))
			{
				case 0: 
					// Menu button	
					stateMachine=stateMenu;
					break;	     
			}
		}
		break;	 	
	}	  
	traceEvent(s_fn,0,"leave [void]");
}
	 
// -----------------------------------------------------------
// SCREEN LOGIC
// -----------------------------------------------------------

/**
 * Draw Text on screen
 * @author wplaat
 */
void drawText(int x, int y, int type, const char *text, ...)
{
   char buf[MAX_LEN];
	memset(buf,0x00,sizeof(buf));
   
	if (text!=NULL)
	{    		
		// Expend event string
		va_list list;
		va_start(list, text );
		vsprintf(buf, text, list);

		switch (type)
		{
			case fontTitle1: 
			{
				if (x==0) x=320-((strlen(buf)*34)/2);  
				GRRLIB_PrintfTTF(x, y, myFont, buf, 72, GRRLIB_BLACK); 
			}
			break;
	   	   	 
			case fontTitle2: 
			{
				if (x==0) x=320-((strlen(buf)*34)/2);  
				GRRLIB_PrintfTTF(x, y, myFont, buf, 72, GRRLIB_WHITESMOKE); 
			}
			break;
  
			case fontWelcome: 
			{
				GRRLIB_PrintfTTF(x, y, myFont, buf, 40, GRRLIB_WHITESMOKE);
			}
			break;
	   
			case fontSubTitle:
			{
				if (x==0) x=320-((strlen(buf)*12)/2);
				GRRLIB_PrintfTTF(x, y, myFont, buf, 24, GRRLIB_BLACK);        
			}
			break;
	   
			case fontParagraph:
			{
				if (x==0) x=320-((strlen(buf)*10)/2);	   
				GRRLIB_PrintfTTF(x, y, myFont, buf, 24, GRRLIB_WHITESMOKE);        
			}
			break;
	   	   
			case fontNormal:
			{
				if (x==0) x=320-((strlen(buf)*7)/2);      
				GRRLIB_PrintfTTF(x, y, myFont, buf, 18, GRRLIB_WHITESMOKE);
			}
			break;
	         
			case fontNew:
			{
				if (x==0) x=320-((strlen(buf)*8)/2);	 
				GRRLIB_PrintfTTF(x, y, myFont, buf, 22, GRRLIB_WHITESMOKE);            
			}
			break;
	   
			case fontSpecial:
			{
				if (x==0) x=320-((strlen(buf)*10)/2);
				GRRLIB_PrintfTTF(x, y, myFont, buf, 10, GRRLIB_WHITESMOKE);        
			}
			break;
	   
			case fontButton:
				if (strlen(buf)==1)
				{           
					GRRLIB_PrintfTTF(x+35, y, myFont, buf, 24, GRRLIB_WHITESMOKE); 
				}
				else
				{  
					GRRLIB_PrintfTTF(x+30, y, myFont, buf, 24, GRRLIB_WHITESMOKE); 
				}		   
				break;
		}
   }
}

/**
 * Draw button on screen.
 *
 * @author wplaat
 */
void drawButtons()
{	
   int i,j;
   
	bool selected=false;
		
   for (i=0; i<maxButtons; i++)
   {
		selected=false;

		//if ((!scrollEnabled) && (strlen(buttons[i].name)==0)) continue;
	  
		for (j=0 ;j<MAX_POINTERS; j++)
		{
			if ((pointers[j].xOffset>=buttons[i].x) && 
				 (pointers[j].xOffset<=buttons[i].x+buttons[i].image->w ) && 
				 (pointers[j].yOffset>=buttons[i].y) && 
				 (pointers[j].yOffset<=buttons[i].y+buttons[i].image->h) )			
			{
				selected=true;
				if (--pointers[j].rumble>0) 
				{
					WPAD_Rumble(j,1); 
				}
				else 
				{
					WPAD_Rumble(j,0);
				}
			}
		}

		if (selected)
      {  
			// Draw selected button
			GRRLIB_DrawImg(buttons[i].x, buttons[i].y, buttons[i].imageSelect, 0, 1, 1, IMAGE_COLOR );		  
		}
		else
		{
			// Draw not selected button
			GRRLIB_DrawImg(buttons[i].x, buttons[i].y, buttons[i].image, 0, 1, 1, IMAGE_COLOR );
		}
		drawText(buttons[i].x,buttons[i].y, fontButton, buttons[i].name);
	}
	
	// If no button selected, stop rumble on all pointers
	if (!selected) 
	{
		for (j=0; j<MAX_POINTERS; j++) 
		{
			WPAD_Rumble(j,0);
			pointers[j].rumble=MAX_RUMBLE;
		}
	}
}

/**
 * draw all blue squares on screen
 * 
 * @author wplaat
 *
 * @param amount	Amount of active blue squares.
 * @param mode		The mode (true=10% transparant|false=50% transparant) 
 */
void drawBlueSquares(int amount, bool mode)
{
   u32 color;
	int i;
	
	if (mode) 
	{
	   color=IMAGE_COLOR;
	}
	else
	{
		color=IMAGE_COLOR2;
	}
	
	for (i=0; i<amount; i++)
	{   
		GRRLIB_DrawImg(
			blueSquares[i].x,
			blueSquares[i].y+yOffset, 
			blueSquares[i].image, 
			0, 1, 1, color );   
	}
}
		

/**
 * draw all red squares on screen
 * 
 * @author wplaat 
 */
void drawRedSquares()
{
	int i;

	for (i=0; i<settings.players; i++)
	{   
		if (redSquares[i].visible)
		{
			GRRLIB_DrawImg(
				redSquares[i].x,
				redSquares[i].y+yOffset, 
				redSquares[i].image, 
				0, 1, 1, IMAGE_COLOR );   
		}
		else
		{
			GRRLIB_DrawImg(
				redSquares[i].x,
				redSquares[i].y+yOffset, 
				redSquares[i].image, 
				0, 1, 1, IMAGE_COLOR2 );   
		}
	}	
}
	
/**
 * Draw Screen
 *
 * @author wplaat 
 */
void drawScreen()
{ 	   
   int 	i=0;
	int  	ypos=yOffset;
	  
	// Calculate new image angle.
	if (++angle>=MAX_ANGLE) angle=0;
	if (size<=MAX_SIZE) size+=0.05;
		
   // Wii DVD light intensity control (fade in and fade out effect)
	if (lightUp)
	{
		if (lightValue<155) 
		{
			lightValue+=3; 
		}
		else 
		{
			lightUp=false;
		}
	}
	else
	{
		if (lightValue>0) 
		{
			lightValue-=3; 
		}
		else 
		{
			lightUp=true;	
		}
	}
	LIGHT(WIILIGHT_SetLevel(lightValue);)
	
   switch( stateMachine )
	{	
	   case stateIntro1:
	   {	  
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
			// Draw background
			GRRLIB_DrawImg(320,(rmode->xfbHeight/2),
				images.logo1, 0, size, size, IMAGE_COLOR );
		  		  
		   ypos+=25;
			drawText(0, ypos, fontParagraph,  "Created by wplaat"  );
			ypos+=20;
			drawText(0, ypos, fontParagraph,  "http://www.plaatsoft.nl"  );
			ypos+=340;
			drawText(40, ypos, fontNormal,  "This software is open source and may be copied, distributed or modified"  );
			ypos+=20;
			drawText(60, ypos, fontNormal,  "under the terms of the GNU General Public License (GPL) version 2" );
		  
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }	   
	   break;
	   
	   case stateIntro2:
	   {
         int  j;
		  
	      // Draw background
			GRRLIB_DrawImg(0,yOffset, images.background3, 0, 1, 1, IMAGE_COLOR );
		  
			// Draw Plaatsoft logo		 
   	   for(j=0;j<images.logo->h;j++)
			{
            GRRLIB_DrawTile(
						((640-images.logo2->w)/2)+sin(wave1)*50, 
						(((480-images.logo2->h)/2)-50)+j, 
						images.logo, 0, 1, 1, IMAGE_COLOR,j );

            wave1+=0.02;
         }
			wave2+=0.02;
         wave1=wave2;
		  	  
			ypos+=320;
			drawText(0, ypos, fontParagraph,  "Please visit my website for more information."  );
			ypos+=40;
			drawText(0, ypos, fontParagraph,  "http://www.plaatsoft.nl"  );
			  
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }	   
	   break;
	   	   
	   case stateIntro3:
	   {
			// Draw Game logo's
			GRRLIB_DrawImg(15, yOffset, images.logo3, 0, 0.95, 0.98, IMAGE_COLOR );
			GRRLIB_DrawImg(320, yOffset,images.logo4, 0, 0.95, 0.98, IMAGE_COLOR );
			GRRLIB_DrawImg(15, 240+yOffset, images.logo5, 0, 0.95, 0.98, IMAGE_COLOR );
			GRRLIB_DrawImg(320, 240+yOffset,images.logo6, 0, 0.95, 0.98, IMAGE_COLOR );
			
			// Draw Plaatsoft logo
         GRRLIB_DrawImg(410, 300+yOffset, 
				images.logo2, 0, 0.5, 0.5, IMAGE_COLOR );

			ypos+=410;
			drawText(350, ypos, fontNormal,  "Some more Wii games developed"  );
			ypos+=20;
			drawText(400, ypos, fontNormal,  "by www.plaatsoft.nl"  );
	   }	   
	   break;
		
		case stateIntro4:
	   { 
			int ypos=185;
			
			// Draw background
			GRRLIB_DrawImg(0, yOffset, images.intro4, 0, 1, 1, IMAGE_COLOR );

			drawText(150, ypos, fontWelcome,  "WarQuest is available" );
			ypos+=45;
			drawText(0, ypos, fontParagraph,  "visit" );
			ypos+=35;
			drawText(200, ypos, fontParagraph,  "http://www.warquest.nl" );
			ypos+=35;
			drawText(190, ypos, fontParagraph,  "and enter the battle zone!" );
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }	   
	   break;
	   	   
	   case stateMenu:
	   {
			char *version;
		  		   
			// Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
         // Draw squares
	      drawBlueSquares(MAX_BLUE_SQUARES, true);
		   
			ypos+=25;
			drawText(20, ypos, fontWelcome, "%s v%s",PROGRAM_NAME, PROGRAM_VERSION);
         ypos+=50;
          
			drawText(20, ypos, fontParagraph, RELEASE_DATE);
			ypos+=255;
		   
         version=tcp_get_version();
         if ( (version!=NULL) && (strlen(version)>0) && (strcmp(version,PROGRAM_VERSION)!=0) )
         {    
	         drawText(20, ypos, fontNew, "New version [v%s] is available.",version);
				ypos+=20;			 			 			 
	         drawText(20, ypos, fontNew, "Check the release notes.");			 
         }  

			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
		  
			// Draw buttons
	      drawButtons(); 
			
			// Move Squares
			moveBlueSquares(MAX_BLUE_SQUARES);
	   }
	   break;
	   
	   case stateGame:
       {      
	      struct tm *level;
				
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
      	
			// Draw Border zone
			GRRLIB_Rectangle(	game.borderSize, 
									game.borderSize+yOffset, 
									MAX_HORZ_PIXELS-(game.borderSize*2), 
									MAX_VERT_PIXELS-(game.borderSize*2), 
									WHITE_TRANSPARANT, 1);

         // Draw blue and red squares
	      drawBlueSquares(game.amountOfBlueSquares, true);
			drawRedSquares();
  
		  	
			// Show play time
			level = localtime(&game.playTime);
			drawText(310, 7+yOffset, fontSpecial, "%02d:%02d:%02d", 
				level->tm_hour, level->tm_min, level->tm_sec);
			
			// Show players score
			for (i=0; i<settings.players; i++)
			{
				switch(i) 
				{
					case 0: drawText(20, 7+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 1: drawText(590, 7+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 2: drawText(20, 460+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 3: drawText(590, 460+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
				}
			}
			
			// Show fps information
			drawText(310, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
  	  
						
			// Move squares
			moveBlueSquares(game.amountOfBlueSquares);
			moveRedSquares();
			
			// Process game events (game over detect, next level, etc..)
			processGameEvents();
	   }
	   break;
	   	   
	   case stateGameOver:
	   {
		   struct tm *level;
				 	
			// Draw background
		   GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		   
			// Draw Border zone
			GRRLIB_Rectangle(	game.borderSize, 
									game.borderSize+yOffset, 
									MAX_HORZ_PIXELS-(game.borderSize*2), 
									MAX_VERT_PIXELS-(game.borderSize*2), 
									WHITE_TRANSPARANT, 1);
									
		   // Draw blue and red squares
	      drawBlueSquares(game.amountOfBlueSquares, false);	
			drawRedSquares();	
      		          
		   // Draw content
			ypos+=170;
		   
			if (game.rating<100)
			{
			   ypos-=80;
			}
			
			drawText(0, ypos, fontTitle1, "GAME OVER   ");
			
			// Play Time
			ypos+=90;
		   drawText(0, ypos, fontSubTitle, "Play Time");
			ypos+=20;
	      level = localtime(&game.playTime);
		   drawText(0, ypos, fontSubTitle, "%02d:%02d:%02d", 
				level->tm_hour, level->tm_min, level->tm_sec);
				
			// Score
			ypos+=40;		
			drawText(295, ypos, fontSubTitle, "Score");
			ypos+=20;
			drawText(0, ypos, fontSubTitle, "%04d", highestScore());

			// New Highest Score
			ypos+=40;
			if (game.rating<100)
			{
				int i;
				drawText(125, ypos, fontSubTitle, "Player %d won, %dth place in highscore!",
					bestPlayer()+1, game.rating+1);				
				
				// Show score stars if top 6 place!
				if (game.rating<6)
				{
					ypos+=30;
				
					for (i=0; i<(6-game.rating); i++) {
						int offset=0;
						if (game.rating%2==0) offset-=30;
						GRRLIB_DrawImg(320-(((5-game.rating)/2)*70)+(i*70)+offset, 
							ypos+32, images.star, angle, 1, 1, IMAGE_COLOR );
					}
				}
			}
			
			// Show play time
			level = localtime(&game.playTime);
			drawText(310, 10+yOffset, fontSpecial, "%02d:%02d:%02d", 
				level->tm_hour, level->tm_min, level->tm_sec);
			
			// Show players score
			for (i=0; i<settings.players; i++)
			{
				switch(i) 
				{
					case 0: drawText(20, 7+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 1: drawText(590, 7+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 2: drawText(20, 460+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
							  
					case 3: drawText(590, 460+yOffset, fontSpecial, "%04d", players[i].score);
							  break;
				}
			}
			
			// Show fps information
			drawText(310, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
	   	   
	   case stateLocalHighScore:
	   {
		   struct tm *local;
			int startEntry;
			int endEntry;
		  		  
			// Draw background
         GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
			
			if (maxLocalHighScore<17)
			{
				startEntry=0;
				endEntry=maxLocalHighScore;
			}
			else
			{
				startEntry=(((float) maxLocalHighScore-17.0)/26.0)*(float)scrollIndex;
				endEntry=startEntry+17;
			}
		  
			// Draw scrollbar
			int ypos2=SCROLLBAR_Y_MIN;
         GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
			for (i=0; i<9; i++) 
			{
				ypos2+=24;
				GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
			}
			ypos2+=24;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
			     	     	
	      // Draw title
			ypos+=15;
	      drawText(0, ypos, fontTitle2, "      Local High Score");	

         // Show Content
         ypos+=90;
			drawText(30, ypos, fontParagraph,  "TOP"  );
	      drawText(90, ypos, fontParagraph,  "LOCAL TIME" );
	      drawText(280, ypos, fontParagraph, "SCORE" );
			drawText(360, ypos, fontParagraph, "NAME"  );
			drawText(440, ypos, fontParagraph, "RATING" );
			ypos+=10;
		  
         for (i=startEntry; i<endEntry; i++)
	      {
  	         if ( highscores[i].localTime != 0 )
				{
					ypos+=16;  
					
					drawText(30, ypos, fontNormal, "%02d", i+1);
	    
	            local = localtime(&highscores[i].localTime);
	    
					drawText(90, ypos, fontNormal, "%02d-%02d-%04d %02d:%02d:%02d", 
						local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
						local->tm_hour, local->tm_min, local->tm_sec);
	   
					drawText(280, ypos, fontNormal, "L%d-%d", 
						highscores[i].level+1,
						highscores[i].score);
						
					drawText(360, ypos, fontNormal, highscores[i].name);
					
					// Show rating stars for top five.
					if (i<6)
					{
						int j;
						for ( j=0; j<(6-i); j++)
						{
							GRRLIB_DrawImg(445+(j*25), ypos+10, images.star, 
								0, 0.3, 0.3, IMAGE_COLOR );
						}
					}
				}
			}	 
		  
         // Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate()); 	   
	   }
	   break;
	   
	   case stateTodayHighScore:
	   {
	      struct tm *local;
			int startEntry;
			int endEntry;
	   
         // Draw background
         GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
				
			if (maxTodayHighScore<17)
			{
				startEntry=0;
				endEntry=maxTodayHighScore;
			}
			else
			{
				startEntry=(((float) maxTodayHighScore-17.0)/26.0)*(float)scrollIndex;
				endEntry=startEntry+17;
			}
     	
			// Draw scrollbar
			int ypos2=SCROLLBAR_Y_MIN;
         GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
			for (i=0; i<9; i++) 
			{
				ypos2+=24;
				GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
			}
			ypos2+=24;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
			
	      // Draw title
			ypos+=15;
	      drawText(0, ypos, fontTitle2, "   Today High Score");	

         // Show Content
         ypos+=90;
	      drawText(30, ypos, fontParagraph,  "TOP"  );
	      drawText(90, ypos, fontParagraph,  "LOCAL TIME" );
	      drawText(280, ypos, fontParagraph, "SCORE" );
			drawText(360, ypos, fontParagraph, "NAME"  );
			drawText(440, ypos, fontParagraph, "LOCATION" );
			ypos+=10;
		  
			if (todayHighScore[0].localTime!=0)
			{
            for (i=startEntry; i<endEntry; i++)
            {
					if ( todayHighScore[i].localTime != 0 )
					{
						ypos+=16;  
						drawText(30, ypos, fontNormal, "%02d", i+1);
			  			  
						local = localtime(&todayHighScore[i].localTime);
						
						drawText(90, ypos, fontNormal, "%02d-%02d-%04d %02d:%02d:%02d", 
							local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
							local->tm_hour, local->tm_min, local->tm_sec);
	   
						drawText(280, ypos, fontNormal, "L%d-%d", 
							todayHighScore[i].level+1,
							todayHighScore[i].score);
	  
						drawText(360, ypos, fontNormal, todayHighScore[i].name);
						drawText(440, ypos, fontNormal, todayHighScore[i].location);
					}
				}			
			}
			else
			{
		      ypos+=120;
		      drawText(0, ypos, fontParagraph, "No information available!");
				ypos+=20;
				drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
			}
			 
         // Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());   
	   }
	   break;
	   
	   case stateGlobalHighScore:
	   {
	      struct tm *local;
		  	int startEntry;
			int endEntry;
			
		   // Draw background
         GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
			
			if (maxGlobalHighScore<17)
			{
				startEntry=0;
				endEntry=maxGlobalHighScore;
			}
			else
			{
				startEntry=(((float) maxGlobalHighScore-17.0)/26.0)*(float)scrollIndex;
				endEntry=startEntry+17;
			}
		   
			// Draw scrollbar
			int ypos2=SCROLLBAR_Y_MIN;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
			for (i=0; i<9; i++) 
			{
				ypos2+=24;
				GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
			}
			ypos2+=24;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
			
	      // Draw title
			ypos+=15;
	      drawText(0, ypos, fontTitle2, "   Global High Score");	

         // Show Content
         ypos+=90;
	      drawText(30, ypos, fontParagraph,  "TOP"  );
	      drawText(90, ypos, fontParagraph,  "LOCAL TIME" );
	      drawText(280, ypos, fontParagraph, "SCORE" );
			drawText(360, ypos, fontParagraph, "NAME"  );
			drawText(440, ypos, fontParagraph, "LOCATION" );
			
			ypos+=10;
			if (globalHighScore[0].localTime!=0)
			{
            for (i=startEntry; i<endEntry; i++)
            {
					if ( globalHighScore[i].localTime != 0 )
					{
						ypos+=16;  
						drawText(30, ypos, fontNormal, "%02d", i+1);
			  			  
						local = localtime(&globalHighScore[i].localTime);
						
						drawText(90, ypos, fontNormal, "%02d-%02d-%04d %02d:%02d:%02d", 
							local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
							local->tm_hour, local->tm_min, local->tm_sec);
	   
						drawText(280, ypos, fontNormal, "L%d-%d", 
							globalHighScore[i].level+1,
							globalHighScore[i].score);
							
						drawText(360, ypos, fontNormal, globalHighScore[i].name);
						drawText(440, ypos, fontNormal, globalHighScore[i].location);
					}
				}			
			}
			else
			{
		      ypos+=120;
		      drawText(0, ypos, fontParagraph, "No information available!");
				ypos+=20;
				drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
			}
			 
          // Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());	   
	   }
	   break;
	   
	   case stateHelp1:
	   {
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
		   // Show title
			ypos+=15;
			drawText(0, ypos, fontTitle2, "Help");
         
			ypos+=120;
			drawText(0, ypos, fontParagraph, "RedSquare is an classic 2D action game.");
			ypos+=25;
			drawText(0, ypos, fontParagraph, "Click and hold the red square.");	
			ypos+=25;
	      drawText(0, ypos, fontParagraph, "Now, move so that you neither touch the walls nor");
			ypos+=25;
	      drawText(0, ypos, fontParagraph, "get hit by any of the blue blocks.");		
			ypos+=25;
	      drawText(0, ypos, fontParagraph, "If you make it to 31 seconds, you are doing brilliantly!");
		
         ypos+=60;
	      drawText(0, ypos, fontParagraph, "Tip: You can control which music track is played during");
			ypos+=25;
	      drawText(0, ypos, fontParagraph, "the game with the 1 and 2 button on your WiiMote!");
				  
			// Draw buttons
	      drawButtons(); 
		  
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
		
		case stateHelp2:
	   {	  
			// Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
 
			// Show title
			ypos+=15;
			drawText(0, ypos, fontTitle2, "WiiMote Control");
		  
			int xoffset=50;
	
         ypos+=100;
			drawText(60+xoffset, ypos,  fontParagraph, "Button");
			drawText(180+xoffset, ypos,  fontParagraph, "Action");
	
			ypos+=50;	  
			drawText(60+xoffset, ypos, fontParagraph, "A");
			drawText(180+xoffset, ypos, fontParagraph, "Select button or scrollbar." ); 

			ypos+=30;	  
			drawText(60+xoffset, ypos, fontParagraph, "B");
			drawText(180+xoffset, ypos, fontParagraph, "Select red square during game." ); 

			ypos+=30;	  
			drawText(60+xoffset, ypos, fontParagraph, "1");
			drawText(180+xoffset, ypos, fontParagraph, "Play next music track." ); 

			ypos+=30;	  
			drawText(60+xoffset, ypos, fontParagraph, "2");
			drawText(180+xoffset, ypos, fontParagraph, "Play previous music track." ); 	

			ypos+=30;	  
			drawText(60+xoffset, ypos, fontParagraph, "+");
			drawText(180+xoffset, ypos, fontParagraph, "Make screenshot." ); 		

			ypos+=30;	  
			drawText(60+xoffset, ypos, fontParagraph, "Home");
			drawText(180+xoffset, ypos, fontParagraph, "Back to main menu / Quit game." );
		  
			// Draw buttons
	      drawButtons();  
		  
		   drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
		}
		break;
   
	   case stateCredits:
	   { 
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		  		
			// Show title
			ypos+=15;
			drawText(0, ypos, fontTitle2, "      Credits");
			  
			// Show Content
	      ypos+=85;
			drawText(0, ypos, fontParagraph, "GAME LOGIC ");
         ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");

	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "GAME GRAPHICS  ");
  	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");
	
	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "MUSIC ");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "modarchive.org  ");

	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "SOUND EFFECTS  ");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");
		   ypos+=15;
	      drawText(0, ypos, fontNormal, "nowhereman");
  
  	      ypos+=30;
	      drawText(0, ypos, fontParagraph, "TESTERS");
	      ypos+=20;
	      drawText(0, ypos, fontNormal, "wplaat");	  
			ypos+=15;
	      drawText(0, ypos, fontNormal, "Harima-kun");	    		  	  	
												
	      ypos+=30;
	      drawText(0, ypos, fontNormal,"Greetings to everybody in the Wii homebrew scene");
		  
			// Draw buttons
	      drawButtons(); 
		  
		   drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
	   	   
	   case stateReleaseNotes:
	   {
			int  i=0;
			int len=0;
			int  lineCount=0;
			int maxLines=0;
			char *buffer;
			char text[MAX_BUFFER_SIZE];
			char tmp[MAX_SIZE];
		  
			int startEntry;
			int endEntry;

	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );

			// Fetch release notes from network thread
			buffer=tcp_get_releasenote();
         if (buffer!=NULL) 
			{
				strncpy(text,buffer,MAX_BUFFER_SIZE);
				len=strlen(text);
				for (i=0;i<len;i++) if (text[i]=='\n') maxLines++;
			}
		  
			// Calculate start and end line.
			if (maxLines<18)
			{
				startEntry=0;
				endEntry=maxLines;
			}
			else
			{
				startEntry=(((float) maxLines-18.0)/26.0)*(float)scrollIndex;
				endEntry=startEntry+18;
			}

			// Draw scrollbar
			int ypos2=SCROLLBAR_Y_MIN;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollTop, 0, 1, 1, IMAGE_COLOR );
			for (i=0; i<9; i++) 
			{
				ypos2+=24;
				GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollMiddle, 0, 1, 1, IMAGE_COLOR );
			}
			ypos2+=24;
			GRRLIB_DrawImg(SCROLLBAR_x,ypos2, images.scrollBottom, 0, 1, 1, IMAGE_COLOR );
				
	      // Draw Title	
			ypos+=15;
         drawText(0, ypos, fontTitle2, "Release Notes");
         
			ypos+=85;
			if (len!=0)
			{		  
				int startpos=0;
				for (i=0; i<len; i++)
				{
					if (text[i]=='\n') 
					{			   
						text[i]=0x00;
				 
						// Show only 17 lines on screen
						if ((lineCount++)>endEntry) break;
						if (lineCount>startEntry) 
						{				   
							ypos+=15;
							sprintf(tmp,"%s",text+startpos);
							drawText(40, ypos, fontNormal, tmp);	
						}		
						startpos=i+1;
					}
				}
			}
			else
			{
				ypos+=120;
				drawText(0, ypos, fontParagraph, "No information available!" );	
				ypos+=20;
				drawText(0, ypos, fontParagraph, "Information could not be fetch from internet.");
			}
		  
			// Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
	   
		case stateSoundSettings:
	   {  
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1, 1, IMAGE_COLOR );
		  
	      // Draw Sound icon
	      GRRLIB_DrawImg( 320, (rmode->xfbHeight/2), 
				images.sound, angle, 1.4, 1.4, IMAGE_COLOR );
				
			// Show title
			ypos+=15;
			drawText(0, ypos, fontTitle2, "   Sound Settings");
         
         // Draw content	
         ypos+=110;
			drawText(0, ypos, fontParagraph, "Music Volume");	
	      ypos+=20;
         GRRLIB_DrawImg(104, ypos, images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      GRRLIB_DrawImg(115+(settings.musicVolume*40),ypos, images.barCursor, 0, 1, 1, IMAGE_COLOR );
  
         ypos+=80;
         drawText(0, ypos, fontParagraph, "Effects Volume" );
	      ypos+=20;	
	      GRRLIB_DrawImg(104,ypos, images.bar, 0, 1, 1, IMAGE_COLOR );
	      ypos+=10;
	      GRRLIB_DrawImg(115+(settings.effectVolume*40),ypos,images.barCursor, 0, 1, 1, IMAGE_COLOR );
	
	      ypos+=70;
	      drawText(0, ypos, fontParagraph, "  Music track [%d]", selectedMusic );	
	  
		   // Draw buttons
	      drawButtons(); 
		  
		   drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
		
	   case stateGameSettings:
	   {		  	         			   
	      // Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1.0, 1.0, IMAGE_COLOR );
      					
	      // Draw Title	
			ypos+=15;
         drawText(0, ypos, fontTitle2, "    Game Settings");
			
         ypos+=95;
			drawText(0, ypos, fontParagraph, "This user name is used in the highscore area.");	
	      
			// Draw text 
			ypos+=70;
			int xpos=75;
			
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[0]);
			xpos+=90;
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[1]);
			xpos+=90;
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[2]);
			xpos+=90;
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[3]);
			xpos+=90;
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[4]);
			xpos+=90;
			drawText(xpos, ypos, fontTitle2, "%c", settings.name[5]);
			
			ypos+=140;
			drawText(460, ypos, fontParagraph, "Random");
			ypos+=20;
			drawText(90,  ypos, fontParagraph, "Players");	
			drawText(260, ypos, fontParagraph, "Game level");	
			drawText(460, ypos, fontParagraph, "Positions");	
	     
		   // Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
	   }
	   break;
		
		case stateDonate:
		{
			// Draw background
			GRRLIB_DrawImg(0, yOffset, images.background1, 0, 1.0, 1.0, IMAGE_COLOR );
      					
			// Draw Title	
			drawText(0, ypos, fontTitle2, "Donate");
			ypos+=100;
			
			drawText(0, ypos, fontParagraph, "If you enjoy this game please send me a");
			ypos+=25;
		   drawText(0, ypos, fontParagraph, "small donation. You can make a donation ");
			ypos+=25;
		   drawText(0, ypos, fontParagraph, "online with your credit card, or paypal account.");
			ypos+=25;
		   drawText(0, ypos, fontParagraph, "Your credit card will be processed by PayPal, a");
			ypos+=25;
		   drawText(0, ypos, fontParagraph, "trusted name in secure online transactions.");
			ypos+=65;
		   drawText(0, ypos, fontParagraph, "Please visit http://www.plaatsoft.nl");			
			ypos+=25;
		   drawText(0, ypos, fontParagraph, "Click on the donate link and follow the instructions.");	
			ypos+=65;
			drawText(0, ypos, fontParagraph, "Many thanks for your support!");

			// Draw buttons
	      drawButtons(); 
			
			drawText(20, 450+yOffset, fontSpecial, "Network: %s",tcp_get_state());
			drawText(20, 460+yOffset, fontSpecial, "%d fps", calculateFrameRate());
		  		   		  		   		 
		}
		break;
	}
}

// -----------------------------------------------------------
// State Machine
// -----------------------------------------------------------

/**
 * Game statemachine
 * @author wplaat
 */
void initStateMachine(void)
{
	char *s_fn="initStateMachine";
			
	// Check if something is change, if no, return direct!
   if (stateMachine==prevStateMachine) return;

	switch(stateMachine)
	{
		case stateIntro1:
		{
			traceEvent(s_fn,0,"stateMachine=stateIntro1");
		
			initButtons();
		
			// Wii DVD light on
			LIGHT(WIILIGHT_TurnOn();)
			lightValue=0;
			lightUp=true;
		}
		break;

		case stateIntro2:
		{
			traceEvent(s_fn,0,"stateMachine=stateIntro2");
			initButtons();
		}
		break;

		case stateIntro3:
		{
			traceEvent(s_fn,0,"stateMachine=stateIntro3");
			initButtons();
		}
		break;		
		
		case stateMenu:
		{
			traceEvent(s_fn,0,"stateMachine=stateMenu");
		   initButtons();
			
			// Wii DVD light off
			LIGHT(WIILIGHT_TurnOff();)
		}
		break;
				
		case stateGame:
		{
			traceEvent(s_fn,0,"stateMachine=stateGame");
		   initButtons();
		}
		break;
		
		case stateGameOver:
		{
			traceEvent(s_fn,0,"stateMachine=stateGameOver");
		   initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)

		}
		break;
		
		case stateLocalHighScore:
		{
			traceEvent(s_fn,0,"stateMachine=stateLocalHighScore");
		   initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;
		
		case stateTodayHighScore:
		{	   
		   traceEvent(s_fn,0,"stateMachine=stateTodayHighScore");
			
			char *buffer=tcp_get_today_highscore();
		   
			loadTodayHighScore(buffer);		     
			
		   initButtons();
		}
		break;
		
		case stateGlobalHighScore:
		{
			traceEvent(s_fn,0,"stateMachine=stateGlobalHighScore");
	   
		   char *buffer=tcp_get_global_highscore();
			
		   loadGlobalHighScore(buffer);		     
			
		   initButtons();
		}
		break;
		
		case stateHelp1:
		{
			traceEvent(s_fn,0,"stateMachine=stateHelp1");
		
			initButtons();
				
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;

		case stateHelp2:
		{
			traceEvent(s_fn,0,"stateMachine=stateHelp2");
		
			initButtons();
		}
		break;
		
		case stateCredits:
		{
			traceEvent(s_fn,0,"stateMachine=stateCredits");
		
		   initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;
		
		case stateSoundSettings:
		{
			traceEvent(s_fn,0,"stateMachine=stateSoundSettings");
		
		   initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;
		
		case stateReleaseNotes:
		{
			traceEvent(s_fn,0,"stateMachine=stateReleaseNotes");
		
		   initButtons();
			noteDelay=0;
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;
		
		case stateGameSettings:
		{
			traceEvent(s_fn,0,"stateMachine=stateGameSettings");
		
		   initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;
		
		case stateDonate:
		{
			traceEvent(s_fn,0,"stateMachine=stateDonate");
		
			initButtons();
			
			// Wii DVD light on
			lightValue=0;
			lightUp=true;
			LIGHT(WIILIGHT_TurnOn();)
		}
		break;		
	} 
	prevStateMachine=stateMachine;
}

// -----------------------------------------------------------
// MAIN
// -----------------------------------------------------------

/**
 * Main start point of game.
 * @author wplaat
 */
int main()
{	
	char *s_fn="main";
	  
   // Init video layer
   VIDEO_Init();
	
  	// Set Shutdown Callbacks.
	SYS_SetPowerCallback( doPowerOff );
	WPAD_SetPowerButtonCallback( doPadPowerOff );
	
   // Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);
		
	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);
	
	if (rmode->xfbHeight==528)
	{
	    // TV mode PAL 50Hz
	    yOffset = 25;  
	}
	else
	{      
	    // TV mode PAL 60Hz
	    yOffset = 0;
	}
   
   // Init Fat
   fatInitDefault();
	
	// Open trace module
	traceOpen(TRACE_FILENAME);
	traceEvent(s_fn, 0,"%s %s Started", PROGRAM_NAME, PROGRAM_VERSION);

	// Load highscore from SD card
   loadLocalHighScoreFile(HIGHSCORE_FILENAME);	
	
	// Load setting from SD card
	loadSettingFile(SETTING_FILENAME);	
	
   // Init Http thread
	initThreads();
	
  	// Init game variables    
	initGame();	

	// Init game images
	initImages();

	// Init pointers
	initPointers();
	
	// init red Squares
   initRedSquares();
	
	// Init blue squares
	initBlueSquares();
	
	// Init sound
	initSound();
	
	// Int global highscore
	initGlobalHighScore();
	
	// Init today highscore
	initTodayHighScore();
   
	// Init Wii DVD rom light thread
	LIGHT(WIILIGHT_Init();)
	
   // Init GRRLib graphics library
   GRRLIB_Init();
   
    // Init FreeType font 
	myFont = GRRLIB_LoadTTF(font_ttf, font_ttf_size); 

    // To have a cool effect anti-aliasing is turned on
    GRRLIB_Settings.antialias = true;
	
	// Black background
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
   
    GRRLIB_Render();
		
	// Init game parameters.
   initGame();
	
	// Init wiimote layer
   WPAD_Init();
	
	// Wiimote is shutdown after 300 seconds of innactivity.
   WPAD_SetIdleTimeout(300); 
	
	// enable accelerometers and IR of the all WiiMotes
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);

	// Scan for button events
	WPAD_SetVRes(0, rmode->fbWidth, rmode->xfbHeight);
	
	// Repeat forever
   while( stateMachine!=stateQuit  )
	{		
      // Process state machine events
	   initStateMachine();
			
      // Draw game board and other items
      drawScreen();		

		// Scan Wii devices
      WPAD_ScanPads();

		int i;
		for (i=0; i<MAX_POINTERS; i++)
		{
		   u32 devtype;
			WPAD_Probe(i,&devtype);
			if (devtype==WPAD_EXP_WIIBOARD)
			{
				//traceEvent(s_fn, 0,"Balance Board id = %d", i);

				// Get balanceboard position
				expansion_t exp;
				WPAD_Expansion(i, &exp);
				
				pointers[i].x=BALL_X+(exp.wb.x*BALL_SENSE_X);
				pointers[i].xOffset=pointers[i].x;
				pointers[i].y=BALL_Y+(exp.wb.y*BALL_SENSE_Y);
				pointers[i].yOffset=pointers[i].y;
				pointers[i].angle=0;	
				
				//traceEvent(s_fn, 0,"x=%d [%d]", pointers[i].x, pointers[i].xOffset);
				//traceEvent(s_fn, 0,"y=%d [%d]", pointers[i].y, pointers[i].yOffset);
			}
			else
			{
				//traceEvent(s_fn, 0,"WiiMote id = %d", i);
			
				// Get button events of WiiMote
				u32 wpadheld = WPAD_ButtonsHeld(i);
				u32 wpaddown = WPAD_ButtonsDown(i);
				u32 wpadup   = WPAD_ButtonsDown(i);

				// Scan for WiiMote IR events 
				ir_t ir;
				WPAD_IR(i, &ir); 
				pointers[i].x=ir.sx-WSP_POINTER_X;
				pointers[i].xOffset=pointers[i].x+IR_X_OFFSET;
				pointers[i].y=ir.sy-WSP_POINTER_Y;
				pointers[i].yOffset=pointers[i].y+IR_Y_OFFSET;
				pointers[i].angle=0; //ir.angle; 

				// Handle "A" button events
				if (wpadheld & BUTTON_A) 
				{
					buttonScroll(i);	
				}
				
				if (wpaddown & BUTTON_A) 
				{
					buttonA(i);	
				}
					
				// handle "B" button events
				if (wpadheld & BUTTON_B) 
				{
					buttonB(i); 
				}
											
				// Handle "1" button events
				if (wpaddown & BUTTON_1) 
				{
					button1x(i);						
				}
			
				if (wpadup & BUTTON_1) 
				{
					selected1=false;
				}
			
				// Handle "2" button events
				if (wpaddown & BUTTON_2) 
				{
					button2y(i);		
				}
			
				if (wpadup & BUTTON_2) 
				{
					selected2=false;
				}
				
				// Handle "Home" button events
				if (wpaddown & BUTTON_HOME) 
				{
					if (stateMachine==stateMenu)
					{
						stateMachine=stateQuit;
					}
					else
					{
						stateMachine=stateMenu;
					}
				}
		
				// Handle plus button events
				if (wpadheld & BUTTON_PLUS)
				{
					// Make screenshots
					buttonPlus(9);	
				}
	
			}
			
			// Draw WiiMote or BalanceBoard pointer.
			GRRLIB_DrawImg( 
				pointers[i].x, 
				pointers[i].y, 
				pointers[i].image, 
				pointers[i].angle, 
				1, 1, IMAGE_COLOR );
		}
		GRRLIB_Render();
	}
	
	// Close Wii Light thread
	LIGHT(WIILIGHT_close();)
	
	GRRLIB_FreeTTF(myFont);
	GRRLIB_Exit();
		
	 // Stop network thread
   tcp_stop_thread();
	
	// Stop rumble
   WPAD_Rumble(0,0);
	
	WPAD_Disconnect(WPAD_CHAN_ALL);

	// Stop music
   MODPlay_Stop(&snd1);
	
	// Stop trace
	traceEvent(s_fn, 0,"Shut the system down");
	traceEvent(s_fn, 0,"%s %s Stopped", PROGRAM_NAME, PROGRAM_VERSION);
	traceClose();
		
	// Reset system, if selected!
	if ( bPowerOff )
	{
		SYS_ResetSystem( SYS_POWEROFF, 0, 0 );
   }

   return 0;
}

// -----------------------------------------------------------
// THE END
// -----------------------------------------------------------
