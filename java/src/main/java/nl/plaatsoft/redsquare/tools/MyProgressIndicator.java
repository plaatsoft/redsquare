package nl.plaatsoft.redsquare.tools;

import javafx.scene.control.ProgressIndicator;

public class MyProgressIndicator extends ProgressIndicator {

	public MyProgressIndicator(int x, int y) {
		
		setMinWidth(150);
		setMinHeight(150);
		    		    
		setLayoutX(x);
		setLayoutY(y);		
	}
}
