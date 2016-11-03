package nl.plaatsoft.redsquare.ui;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Orientation;
import javafx.scene.control.ScrollBar;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class ReleaseNotes extends MyPanel {
	
	private static String[] version = {
						
	        "01-11-2016 (Version 0.2)\n"
			+ "- Protect blue squares against size hacking.\n"
			+ "- Protect red square against size hacking.\n"
			+ "- Added scrollbar to release notes page.\n"
			+ "- Added CGI master hackers to credits page.\n"
			+ "- Improve webservice calls.\n"
			+ "- Check java version. If version is outdated, warn user.\n"
			+ "- Show warning when internet connection is down.\n",
	
			"30-10-2016 (Version 0.1)\n"
			+ "- Added basic sound effects.\n"
			+ "- Added nice background music.\n"
			+ "- Added webservice to store local and global highscore.\n"
			+ "- Added new version check thread to home page.\n"
			+ "- Added page navigator so pages are loaded just in time.\n"
			+ "- Added game page with special effects.\n"
			+ "- Added two intro pages with basic animation.\n"
			+ "- Added help, credits, release notes and donate page.\n"};

	private static MyLabel text;
	
	public void draw() {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	    	  
    	setBackground(background);
    	
    	 ScrollBar s1 = new ScrollBar();
    	 s1.setMin(0);
    	 s1.setMax(version.length-1);         
         s1.setValue(0);
         s1.setUnitIncrement(1);
         s1.setBlockIncrement(1);
         s1.setLayoutX(590);
         s1.setLayoutY(125);
         s1.setMinWidth(25);
         s1.setMinHeight(275);
         s1.setOrientation(Orientation.VERTICAL);
         
         s1.valueProperty().addListener(new ChangeListener<Number>() {
             public void changed(ObservableValue<? extends Number> ov, Number old_val, Number new_val) {
            	 text.setText(version[new_val.intValue()]);
             }
         });
         
         getChildren().add(s1);
                  
    	getChildren().add( new MyLabel(0, 20, "Release Notes", 60, "white", "-fx-font-weight: bold;"));
    	text = new MyLabel(30, 120, version[0], 20, "white");
    	getChildren().add( text );    	
    	getChildren().add( new MyButton(230, 420, "Close", 18, Navigator.HOME));     
	}
}
