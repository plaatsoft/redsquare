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

public class Donate extends MyPanel {

	public void draw() {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	
    	setBackground(background);
    	
    	int y=20;
    	getChildren().add(new MyLabel(0, y, "Donate", 60, "white"));
    	y+=80;
    	getChildren().add(new MyLabel(0, y, "If you enjoy this game, please sent me a", 24, "white"));
    	y+=30;
    	getChildren().add(new MyLabel(0, y, "small donation. You can make a donation", 24, "white"));
    	y+=30;
    	getChildren().add(new MyLabel(0, y, "online with your credit card, or PayPal account.", 24, "white"));
    	y+=30;    	 
    	getChildren().add(new MyLabel(0, y, "Your credit card will be processed by PayPal, a", 24, "white"));
    	y+=30;
    	getChildren().add(new MyLabel(0, y, "trusted name in secure online transactions.", 24, "white"));
    	y+=60;
    	getChildren().add(new MyLabel(0, y, "Please visit www.plaatsoft.nl", 24, "white"));
    	y+=30;
    	getChildren().add(new MyLabel(0, y, "Click on the donate link and follow the instructions", 24, "white"));    	
    	y+=60;
    	getChildren().add(new MyLabel(0, y, "Many thanks for your support!", 24, "white"));
    	       		
    	getChildren().add(new MyButton(230, 420, "Close", 18, Navigator.HOME));		
		
	}
	
}
