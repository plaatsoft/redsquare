package nl.plaatsoft.redsquare.ui;

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;

import java.text.SimpleDateFormat;
import java.util.Iterator;

import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreGlobal;

public class HighScore2 extends Pane {
		   
	private final static SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-YYYY HH:mm:ss");
	
	private int y;
	private int lines; 
	
	HighScore2(final Navigator page) {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
		setBackground(background);
		
		y=0;
		getChildren().add(new MyLabel(0, y, "Global High Score", 50, "white"));		
		                
    	y+=60;    	
    	getChildren().add(new MyLabel(30, y, "Nr", 30, "white"));
    	getChildren().add(new MyLabel(90, y, "Date", 30, "white"));
		getChildren().add(new MyLabel(300, y, "Score", 30, "white"));	
		getChildren().add(new MyLabel(400, y, "Name", 30, "white"));
		y+=20;
				
		lines=1;
    	Iterator<Score> iter = ScoreGlobal.getScore().iterator();    	
		while (iter.hasNext()) {
			y+=20;
			
			Score score = (Score) iter.next();	
			getChildren().add(new MyLabel(30, y, ""+lines, 20, "white"));					
			getChildren().add(new MyLabel(90, y, formatter.format(score.getTimestamp()), 20, "white"));
			getChildren().add(new MyLabel(300, y, ""+score.getScore(), 20, "white"));	
			getChildren().add(new MyLabel(400, y, ""+score.getUser(), 20, "white"));
			
			if (++lines>15) {
				break;
			}
		}
		
		MyButton button1 = new MyButton(230, 420, "Close", 18, page, page.getHome());
		getChildren().add(button1);	
	}
}
