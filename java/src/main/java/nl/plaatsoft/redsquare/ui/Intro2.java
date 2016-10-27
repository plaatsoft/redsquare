package nl.plaatsoft.redsquare.ui;

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

public class Intro2 extends Pane {

	private ImageView imageView;
	private AnimationTimer timer;
	
	Intro2(final Navigator page) {
		
		Image image1 = new Image("images/background2.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		
		Label label1 = new Label("Please vist my website for more information");
		label1.setLayoutX(120);
		label1.setLayoutY(50);
		label1.setStyle("-fx-font-size:20px; -fx-text-fill: white;");
		
		Label label2 = new Label("http://www.plaatsoft.nl");
		label2.setLayoutX(220);
		label2.setLayoutY(70);
		label2.setStyle("-fx-font-size:20px; -fx-text-fill: white;");
		
		Label label3 = new Label("RedSquare is also available for Nintendo Wii and Android");
		label3.setLayoutX(60);
		label3.setLayoutY(400);
		label3.setStyle("-fx-font-size:20px; -fx-text-fill: white;");
		
		Image image2 = new Image("images/logo2.png");
		imageView = new ImageView();
		imageView.setImage(image2);
		imageView.setLayoutX(200);
		imageView.setLayoutY(150);
								
		setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(imageView);
		getChildren().add(label3);
		
		setOnMousePressed(new EventHandler<MouseEvent>() {

	        public void handle(MouseEvent t) {
				page.setHome();						
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
	}
	
	void draw() {		
		timer.start();
	}
}
