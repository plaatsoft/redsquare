/**
 *  @file
 *  @brief 
 *  @author wplaat
 *
 *  Copyright (C) 2008-2016 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
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

package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.animation.AnimationTimer;
import javafx.concurrent.Task;

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import nl.plaatsoft.redsquare.network.CloudNewVersion;
import nl.plaatsoft.redsquare.resources.Square;
import nl.plaatsoft.redsquare.resources.Squares;
import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class Home extends MyPanel {

	final static Logger log = Logger.getLogger( Home.class);
	
	private Square blue1;
	private Square blue2;
	private Square blue3;
	private Square blue4;
	private Square red;
		
	private AnimationTimer timer;
	private MyLabel label3;
	private String upgrade;
	private Task<Void> task;
	
	Home () {
		
		int step = 1;
		
		blue1 = new Square(Squares.getBlue1(), 30, 30, 1, 1, step, false);
		blue2 = new Square(Squares.getBlue2(), 500, 30, 1, 0, step, false);
		blue3 = new Square(Squares.getBlue3(), 30, 400, 0, 1 ,step, false);
		blue4 = new Square(Squares.getBlue4(), 500, 400, 0, 0 , step, false);
		red = new Square(Squares.getRed(), 10, 10, 0, 0, 2, false);
					
		getChildren().add(blue1);
		getChildren().add(blue2);    	
		getChildren().add(blue3);    	
		getChildren().add(blue4);    
		getChildren().add(red);    
			
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		setBackground(background);
		
		getChildren().add (new MyLabel(30, 30, Constants.APP_NAME+" v"+Constants.APP_VERSION, 30, "white", "-fx-font-weight: bold;"));		
		getChildren().add (new MyLabel(30, 70, Constants.APP_BUILD, 20));
		label3 = new MyLabel(30, 420, "", 20, "white");
		getChildren().add(label3);
				
		int y = 30;
		getChildren().add( new MyButton(430, y, "Play", 18, Navigator.GAME));
		y += 45;
		getChildren().add( new MyButton(430, y, "High Score", 18, Navigator.LOCAL_HIGHSCORE));
		y += 45;	
		getChildren().add( new MyButton(430, y, "Settings", 18, Navigator.SETTINGS));
		y += 45;
		getChildren().add( new MyButton(430, y, "Help", 18, Navigator.HELP));
		y += 45;
		getChildren().add( new MyButton(430, y, "Credits", 18, Navigator.CREDITS));
		y += 45;
		getChildren().add( new MyButton(430, y, "Release Notes", 18, Navigator.RELEASE_NOTES));
		y += 45;
		getChildren().add( new MyButton(430, y, "Donate", 18, Navigator.DONATE));
		
		y = Constants.HEIGHT-70;
		getChildren().add( new MyButton(430, y, "Exit", 18, Navigator.EXIT));	
			
				
		timer = new AnimationTimer() {
			 
	       @Override
	       public void handle(long now) {
	          	blue1.move();
	           	blue2.move();
	           	blue3.move();
	           	blue4.move();
	           	red.move();
	            label3.setText(upgrade);
	       	}
	    };
			    
	    task = new Task<Void>() {
	        public Void call() {
	           	 upgrade = CloudNewVersion.get(); 
	            return null;
	        }
		};
    }
	
	public void draw() {		
		timer.start();
		new Thread(task).start();
	}
}
