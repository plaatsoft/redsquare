package nl.plaatsoft.redsquare.ui;

import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;

public class Credits extends Pane {

	Credits(final Navigator page) {
			
		Image image1 = new Image("images/background1.png");
	    BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
	    BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
	    Background background = new Background(backgroundImage);
	    	
	    int y=60;
	    MyLabel label1 = new MyLabel(230, 20, "Credits", 60);
	    y+=60;
	    MyLabel label2 = new MyLabel(250, y, "GAME LOGIC", 26);
	    y+=30;
	    MyLabel label3 = new MyLabel(300, y, "wplaat", 16);
	    y+=25;
	    MyLabel label4 = new MyLabel(230, y, "GAME GRAPHICS", 26);
	    y+=30;    	 
	    MyLabel label5 = new MyLabel(300, y, "wplaat", 14);
	    y+=25;
	    MyLabel label6 = new MyLabel(280, y, "MUSIC", 26);
	    y+=30;
	    MyLabel label7 = new MyLabel(270, y, "modarchive.org", 14);
	    y+=25;
	    MyLabel label8 = new MyLabel(230, y, "SOUND EFFECTS", 26);
	    y+=30;
	    MyLabel label9 = new MyLabel(300, y, "wplaat", 16);
	    y+=25;
	    MyLabel label10 = new MyLabel(270, y, "TESTERS", 26);
	    y+=30;
	    MyLabel label11 = new MyLabel(300, y, "wplaat", 16);
	    	     
	    MyButton button1 = new MyButton(230, 420, "Close", 18, page, page.getHome());
	    	                
	    setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(label3);
		getChildren().add(label4);
		getChildren().add(label5);
		getChildren().add(label6);
		getChildren().add(label7);
		getChildren().add(label8);		
		getChildren().add(label9);		
		getChildren().add(label10);		
		getChildren().add(label11);		
		getChildren().add(button1);
	}
}
