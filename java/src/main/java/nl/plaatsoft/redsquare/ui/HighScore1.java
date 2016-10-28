package nl.plaatsoft.redsquare.ui;

import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;

import java.text.SimpleDateFormat;
import java.util.Iterator;

import nl.plaatsoft.redsquare.network.CloudScore;
import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreLocal;

public class HighScore1 extends Pane {
		   
	private final static SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-YYYY HH:mm:ss");
	
	private int y;
	private int lines; 
	private Task<Void> task;
	
	HighScore1(final Navigator page) {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
		setBackground(background);
		
		y=0;    
		getChildren().add (new MyLabel(0, y, "Local High Score", 50, "white"));		
		                
    	y+=60;    	
    	getChildren().add(new MyLabel(30, y, "Nr", 30, "white"));
    	getChildren().add(new MyLabel(90, y, "Date", 30, "white"));
		getChildren().add(new MyLabel(300, y, "Score", 30, "white"));	
		getChildren().add(new MyLabel(400, y, "Level", 30, "white"));
		getChildren().add(new MyLabel(490, y, "Award", 30, "white"));	
		y=y+20;
				
		lines=1;
    	Iterator<Score> iter = ScoreLocal.getScore().iterator();    	
		while (iter.hasNext()) {
			y+=20;
			Score score = (Score) iter.next();	
			getChildren().add(new MyLabel(30, y, ""+lines, 20, "white"));					
			getChildren().add(new MyLabel(90, y, formatter.format(score.getTimestamp()), 20, "white"));
			getChildren().add(new MyLabel(300, y, ""+score.getScore(), 20, "white"));	
			getChildren().add(new MyLabel(400, y, ""+score.getLevel(), 20, "white"));	
			
			if (lines<6) {
				for (int x=0; x<(6-lines); x++) {
					getChildren().add( new MyImageView(470+(x*25),y-20, "images/star.png", 0.4));
				}
			}
			
			if (++lines>15) {
				break;
			}
		}
		
		MyButton button1 = new MyButton(230, 420, "Next", 18, page, page.getHighScore2());		
		button1.setOnAction(new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent event) {
            	page.setHighScore2();
            }
        });
		getChildren().add(button1);			
		
		task = new Task<Void>() {
	        public Void call() {
	           	CloudScore.getGlobal(Constants.APP_WS_NAME, Constants.APP_VERSION); 
	            return null;
	        }
		};
	}
	
	void draw() {				
		new Thread(task).start();
	}
}
