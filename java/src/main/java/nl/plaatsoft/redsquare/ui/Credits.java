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

public class Credits extends MyPanel {

	@Override
	public void draw() {
		
		Image image1 = new Image("images/background1.png");
	    BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
	    BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
	    Background background = new Background(backgroundImage);
	    	
	    setBackground(background);
	    
	    int y=20;
	    getChildren().add( new MyLabel(0, y, "Credits", 60, "white", "-fx-font-weight: bold;"));
	    y+=80;
	    getChildren().add( new MyLabel(0, y, "GAME LOGIC", 24, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "wplaat", 18, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "GAME GRAPHICS", 24, "white"));
	    y+=30;    	 
	    getChildren().add( new MyLabel(0, y, "wplaat", 18, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "MUSIC & SOUND EFFECTS", 24, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "wplaat", 18, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "TESTERS", 24, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "wplaat, lplaat, splaat, bplaat,", 18, "white"));
	    y+=30;
	    getChildren().add( new MyLabel(0, y, "mriel, epronk, rsiemonsma, rboedhoer", 18, "white"));
	    	     
	    getChildren().add( new MyButton(230, 420, "Close", 18, Navigator.HOME));		
	}
}
