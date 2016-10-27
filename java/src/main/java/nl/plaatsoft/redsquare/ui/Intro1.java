package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.animation.AnimationTimer;
import javafx.event.EventHandler;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;

public class Intro1 extends Pane {

	final static Logger log = Logger.getLogger( Intro1.class);
	
	private ImageView imageView;
	private AnimationTimer timer;
	
	Intro1(final Navigator page) {
		
		log.info("enter");
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		
		Label label1 = new Label("Created by PlaatSoft");
		label1.setLayoutX(220);
		label1.setLayoutY(30);
		label1.setStyle("-fx-font-size:26px; -fx-text-fill: white;");
		
		Label label2 = new Label("http://www.plaatsoft.nl");
		label2.setLayoutX(200);
		label2.setLayoutY(70);
		label2.setStyle("-fx-font-size:26px; -fx-text-fill: white;");
		
		Image image2 = new Image("images/logo.png");
		imageView = new ImageView();
		imageView.setImage(image2);
		imageView.setLayoutX(80);
		imageView.setLayoutY(150);
		
		Label label3 = new Label("This is source is open source and may be copied, distributed or modified");
		label3.setLayoutX(30);
		label3.setLayoutY(400);
		label3.setStyle("-fx-font-size:18px; -fx-text-fill: white;");
		
		Label label4 = new Label("under the terms of the GNU General Public License (GPL) version 3.");
		label4.setLayoutX(50);
		label4.setLayoutY(420);
		label4.setStyle("-fx-font-size:18px; -fx-text-fill: white;");
									
		setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(imageView);
		getChildren().add(label3);
		getChildren().add(label4);
		
		setOnMousePressed(new EventHandler<MouseEvent>() {

	        public void handle(MouseEvent t) {
				page.setIntro2();						
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
	       	imageView.setScaleX(size);
	       	imageView.setScaleY(size);
	    }	   
      };
      log.info("leave");
	}
	
	void draw() {		
		timer.start();
	}
}
