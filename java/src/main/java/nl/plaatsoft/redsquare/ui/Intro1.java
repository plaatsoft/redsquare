package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.animation.AnimationTimer;
import javafx.concurrent.Task;
import javafx.event.EventHandler;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import nl.plaatsoft.redsquare.network.CloudProduct;
import nl.plaatsoft.redsquare.network.CloudScore;
import nl.plaatsoft.redsquare.network.CloudUser;
import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class Intro1 extends MyPanel {

	final static Logger log = Logger.getLogger( Intro1.class);
	
	private MyImageView imageView1;
	private AnimationTimer timer;
	private Task<Void> task;
	
	public Intro1() {
	
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		setBackground( new Background(backgroundImage));
		
		getChildren().add( new MyLabel(0,30,"Created by PlaatSoft",26, "white"));
		getChildren().add( new MyLabel(0,70,"www.plaatsoft.nl",26, "white"));
		imageView1 = new MyImageView(80,150, "images/logo1.png",1);		
		getChildren().add(imageView1);
		getChildren().add( new MyLabel(0,410,"This software is open source and may be copied, distributed or modified",16, "white"));
		getChildren().add( new MyLabel(0,430,"under the terms of the GNU General Public License (GPL) version 3",16, "white"));
		
		setOnMousePressed(new EventHandler<MouseEvent>() {
	        public void handle(MouseEvent t) {
	        	Navigator.go(Navigator.INTRO2);			
	        }
	    });		
	}
	
	public void draw() {		
				
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
	    
	    task = new Task<Void>() {
	        public Void call() {
	           	CloudProduct.getPid(); 
	            CloudUser.getUid();
	            CloudScore.getLocal(); 	            
	            return null;
	        }
		};
		
		timer.start();
		new Thread(task).start();
	}
}
