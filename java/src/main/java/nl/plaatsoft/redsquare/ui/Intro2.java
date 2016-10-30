package nl.plaatsoft.redsquare.ui;

import javafx.animation.AnimationTimer;
import javafx.event.EventHandler;
import javafx.scene.image.Image;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class Intro2 extends MyPanel {

	private MyImageView imageView1;
	private AnimationTimer timer;
	
	Intro2() {
		
		Image image1 = new Image("images/background2.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		
		MyLabel label1 = new MyLabel(0,30,"For more information visit",26, "white");
		MyLabel label2 = new MyLabel(0,70,"www.plaatsoft.nl",26, "white");
		imageView1 = new MyImageView(200,150, "images/logo2.png",1);		
		MyLabel label3 = new MyLabel(0,410,"RedSquare is also available for Nintendo Wii",16, "white");
												
		setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(imageView1);
		getChildren().add(label3);
		
		setOnMousePressed(new EventHandler<MouseEvent>() {

	        public void handle(MouseEvent t) {
				Navigator.go(Navigator.HOME);						
	        }
	    });
				
		timer = new AnimationTimer() {			 
		float size = (float) 0.025;
			 	
	    @Override
	    public void handle(long now) {
	            	
	       	size+=0.025;
	       	if (size>=1) {
	       		size=1;
	       	}
	       	imageView1.setScaleX(size);
	       	imageView1.setScaleY(size);
	      }
	    };		
	}
	
	public void draw() {		
		timer.start();
	}
}
