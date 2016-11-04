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

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import java.text.SimpleDateFormat;
import java.util.Iterator;

import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreLocal;

public class HighScore1 extends MyPanel {
		   
	private final static SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-YYYY HH:mm:ss");
	
	private int y;
	private int lines; 
		
	public void draw() {	
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
		setBackground(background);
		
		y=0;    
		getChildren().add (new MyLabel(0, y, "Personal High Score", 50, "white", "-fx-font-weight: bold;"));		
		                
    	y+=60;    	
    	getChildren().add(new MyLabel(30, y, "Nr", 30));
    	getChildren().add(new MyLabel(80, y, "Date", 30));
		getChildren().add(new MyLabel(300, y, "Score", 30));	
		getChildren().add(new MyLabel(400, y, "Level", 30));
		getChildren().add(new MyLabel(490, y, "Awards", 30));	
		y=y+20;
				
		lines=1;
    	Iterator<Score> iter = ScoreLocal.getScore().iterator();    	
		while (iter.hasNext()) {
			y+=20;
			Score score = (Score) iter.next();	
			getChildren().add(new MyLabel(30, y, ""+lines, 20));					
			getChildren().add(new MyLabel(80, y, formatter.format(score.getTimestamp()), 20));
			getChildren().add(new MyLabel(300, y, ""+score.getScore(), 20));	
			getChildren().add(new MyLabel(400, y, ""+score.getLevel(), 20));	
			
			if (lines<6) {
				for (int x=0; x<(6-lines); x++) {
					getChildren().add( new MyImageView(470+(x*25),y-20, "images/star.png", 0.4));
				}
			}
			
			if (++lines>15) {
				break;
			}
		}
		
		getChildren().add( new MyButton(230, 420, "Next", 18, Navigator.GLOBAL_HIGHSCORE));				
	}
}
