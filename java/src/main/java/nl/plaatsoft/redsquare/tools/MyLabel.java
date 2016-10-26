package nl.plaatsoft.redsquare.tools;

import javafx.scene.control.Label;

public class MyLabel extends Label {

	public MyLabel(int x, int y, String value, int fontSize) {
		setText(value);
		setLayoutX(x);
		setLayoutY(y);
		setStyle("-fx-font-size:"+fontSize+"px; -fx-text-fill: white;");
	}	
}
