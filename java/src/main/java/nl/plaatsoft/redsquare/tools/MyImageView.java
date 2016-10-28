package nl.plaatsoft.redsquare.tools;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class MyImageView extends ImageView {
	
	public MyImageView(int x, int y, String resource, double scale) {
		        
		Image image = new Image(resource);
		setImage(image);
		setLayoutX(x);
		setLayoutY(y);
		setScaleX(scale);
		setScaleY(scale);
	}
}
