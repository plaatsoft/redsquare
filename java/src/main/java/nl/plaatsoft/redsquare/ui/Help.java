package nl.plaatsoft.redsquare.ui;

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class Help extends MyPanel {

	public void draw() {
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	    	
    	setBackground(background);
    	
    	int y=20;
    	getChildren().add( new MyLabel(0, y, "Help", 60, "white", "-fx-font-weight: bold;"));
    	y+=120;
    	getChildren().add( new MyLabel(0, y, "RedSquare is an classic 2D action game.", 24));
    	y+=30;
    	getChildren().add( new MyLabel(0, y, "Click and hold the red square.", 24));
    	y+=30;
    	getChildren().add( new MyLabel(0, y, "Now move so that you neither touch the wall", 24));
    	y+=30;    	 
    	getChildren().add( new MyLabel(0, y, "nor get hit by any of the blue squares.", 24));
    	y+=30;
    	getChildren().add( new MyLabel(0, y, "If you make it to 40 seconds, you are doing", 24));
    	y+=30;
    	getChildren().add( new MyLabel(0, y, "brilliantly!", 24));
    	       		
    	getChildren().add( new MyButton(230, 420, "Close", 18, Navigator.HOME));		
	}
}
