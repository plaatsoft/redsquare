package nl.plaatsoft.redsquare.ui;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

import javafx.animation.AnimationTimer;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;

public class Game extends Pane {

	private Square blue1;
	private Square blue2;
	private Square blue3;
	private Square blue4;
	private Square red;	
	private int score = 0;
	private int level = 1;
	private Date starttime = new Date();
	private Date leveltime = new Date(); 
	private Label label1;
	private Label label2;
	private Label label3;	
	private SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");
	private int move = 0; 
	private int step = 1;
	private double width = 640;
	private double height = 480;
				
	public void restart() {
		starttime = new Date();
		leveltime = new Date(); 
		score = 0;
		level = 1;
		
		blue1.setPosition(0, 0);
		blue2.setPosition(500, 300);
		blue3.setPosition(0, 400);
		blue4.setPosition(500, 200);
	}
	
	Game(final Navigator page) {
					
		formatter.setTimeZone(TimeZone.getTimeZone("GMT"));
		
		Image image1 = new Image("images/background.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		
		blue1 = new Square("bluesquare1.png", 0, 0, 1, 1, step, width, height);
		blue2 = new Square("bluesquare2.png", 500, 30, 1, 0, step, width, height);
		blue3 = new Square("bluesquare3.png", 0, 400, 0, 1 ,step, width, height);
		blue4 = new Square("bluesquare4.png", 500, 400, 0, 0 , step, width, height);
		red = new Square("redsquare.png", 300, 200, 0, 0, 0, width, height);		
		red.setLayoutX(300);
    	red.setLayoutY(200);
    	
		red.setOnMousePressed(new EventHandler<MouseEvent>() {
		    public void handle(MouseEvent me) {
		        System.out.println("Mouse pressed "+me.getSceneX()+" "+me.getSceneY());	
		        move = 1; 
		    }
		});
		
		red.setOnMouseDragged(new EventHandler<MouseEvent>() {
		    public void handle(MouseEvent me) {
		    	
		    	System.out.println("Mouse move "+me.getSceneX()+" "+me.getSceneY()+" "+move);	
		    	red.setLayoutX(me.getSceneX());
		    	red.setLayoutY(me.getSceneY());
		    }
		});
		
		red.setOnMouseReleased(new EventHandler<MouseEvent>() {
		    public void handle(MouseEvent me) {
		        System.out.println("Mouse released "+me.getSceneX()+" "+me.getSceneY());
		        
		        move = 0; 
		    }
		});
	
		label1 = new Label("0");
		label1.setLayoutX(10);
		label1.setLayoutY(10);
		label1.setStyle("-fx-font-size:24px; -fx-text-fill: white;");
	
		label2 = new Label("00:00:00");
		label2.setLayoutX(280);
		label2.setLayoutY(10);
		label2.setStyle("-fx-font-size:24px; -fx-text-fill: white;");
		
		label3 = new Label("0");
		label3.setLayoutX(600);
		label3.setLayoutY(10);
		label3.setStyle("-fx-font-size:24px; -fx-text-fill: white;");
	
		Button btn1 = new Button();
		btn1.setText("Exit");
		btn1.setLayoutX(450);
		btn1.setLayoutY(410);
		btn1.setPrefWidth(150);
		btn1.setStyle("-fx-font-size:18px;");
		btn1.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				System.out.println("Exit");
				page.setHome();
			}
		});
        			
		setBackground(background);
		getChildren().add(blue1);
		getChildren().add(blue2);    	
		getChildren().add(blue3);    	
		getChildren().add(blue4);    
		getChildren().add(red);    
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(label3);   	
		getChildren().add(btn1);
		
		 AnimationTimer timer1 = new AnimationTimer() {
			 
	            @Override
	            public void handle(long now) {
	            	blue1.move();
	            	blue2.move();
	            	blue3.move();
	            	blue4.move();
	           
	            	score++;
	            	label1.setText(""+score);
	            	
	            	Date current = new Date();	            	
	            	long diff1 = current.getTime() - starttime.getTime();
	            	long diff2 = current.getTime() - leveltime.getTime();

	            	if ( diff2>10000 ) {
	            		leveltime = new Date(); 
	            		level++;
	       	            		
	            		blue1.setStep(blue1.getStep()+1);
	            		blue2.setStep(blue2.getStep()+1);	
	            		blue3.setStep(blue3.getStep()+1);	
	            		blue4.setStep(blue4.getStep()+1);	
	            	}
	            	label3.setText(""+level);
	            	label2.setText(""+formatter.format(diff1));
	            }
	        };	        
	        timer1.start();
	}
}
