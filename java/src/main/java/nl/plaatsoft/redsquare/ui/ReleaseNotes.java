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

public class ReleaseNotes extends Pane {

	String notes="29-10-2016 (Version 0.1)\n"
			+ "- Added basic sound effects.\n"
			+ "- Added nice background music.\n"
			+ "- Added webservice to store local and global highscore.\n"
			+ "- Added new version check thread to home page.\n"
			+ "- Added page navigator so pages are loaded just in time.\n"
			+ "- Added game page with special effects.\n"
			+ "- Added two intro pages with basic animation.\n"
			+ "- Added help, credits, release notes and donate page.\n";
	
	ReleaseNotes(final Navigator page) {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	    	   	
    	MyLabel label1 = new MyLabel(0, 20, "Release Notes", 60, "white");
    	MyLabel label2 = new MyLabel(30, 120, notes, 20, "white");    	
    	MyButton button1 = new MyButton(230, 420, "Close", 18, page, page.getHome());
                      
		setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(button1);
	}
}
