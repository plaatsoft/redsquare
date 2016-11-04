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

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

import javafx.concurrent.Task;
import javafx.concurrent.Worker;
import javafx.concurrent.Worker.State;

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import java.text.SimpleDateFormat;
import java.util.Iterator;

import nl.plaatsoft.redsquare.network.CloudScore;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreGlobal;

public class HighScore2 extends MyPanel {
		   
	private final static SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-YYYY HH:mm:ss");
	
	private int y;
	private int lines; 
	private Task<Void> task;
			
	private void showTable() {
		
		y=80;
				
		lines=1;
    	Iterator<Score> iter = ScoreGlobal.getScore().iterator();    	
		while (iter.hasNext()) {
			y+=20;
			
			Score score = (Score) iter.next();	
			getChildren().add(new MyLabel(30, y, ""+lines, 20));					
			getChildren().add(new MyLabel(80, y, formatter.format(score.getTimestamp()), 20));
			getChildren().add(new MyLabel(300, y, ""+score.getScore(), 20));	
			
			if (score.getCountry().length()>0) {
				try { 
					getChildren().add(new MyImageView(397,y+4,"images/flags/"+score.getCountry()+".png", 0.7));
				} catch (Exception e) {
					// flag filename not found
				}
			}
			getChildren().add(new MyLabel(430, y, ""+score.getNickname(), 20));
			
			if (++lines>15) {
				break;
			}
		}
	}
	
	public void draw() {
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
		setBackground(background);
		
		y=0;
		getChildren().add(new MyLabel(0, y, "Ultimate High Score", 50, "white", "-fx-font-weight: bold;"));		
				
		y+=60;    	
    	getChildren().add(new MyLabel(30, y, "Nr", 30));
    	getChildren().add(new MyLabel(80, y, "Date", 30));
		getChildren().add(new MyLabel(300, y, "Score", 30));	
		getChildren().add(new MyLabel(400, y, "Nickname", 30));
				
		MyButton button1 = new MyButton(230, 420, "Close", 18, Navigator.HOME);
		
		getChildren().add(button1);	
				
		task = new Task<Void>() {
	        public Void call() {
	           	CloudScore.getGlobal(); 
	            return null;
	        }
		};
		
		task.stateProperty().addListener(new ChangeListener<Worker.State>() {

	        public void changed(ObservableValue<? extends State> observable, State oldValue, Worker.State newState) {
	            if(newState==Worker.State.SUCCEEDED){
	            	showTable();
	            }
	        }
	    });		
		
		new Thread(task).start();		
	}
}
