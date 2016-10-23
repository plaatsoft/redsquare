package nl.plaatsoft.redsquare;

import javafx.animation.AnimationTimer;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;

public class Home extends Pane {

	private Square blue1;
	private Square blue2;
	private Square blue3;
	private Square blue4;
	private Square red;
		
	Home (final Navigator page) {
			
		Image image1 = new Image("images/background.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
	
		int step = 1;
		double width = 640;
		double height = 480;
		
		blue1 = new Square("bluesquare1.png", 30, 30, 1, 1, step, width, height);
		blue2 = new Square("bluesquare2.png", 500, 30, 1, 0, step, width, height);
		blue3 = new Square("bluesquare3.png", 30, 400, 0, 1 ,step, width, height);
		blue4 = new Square("bluesquare4.png", 500, 400, 0, 0 , step, width, height);
		red = new Square("redsquare.png", 10, 10, 0, 0, 5, width, height);
	
		Label label1 = new Label("RedSquare v1.0");
		label1.setLayoutX(30);
		label1.setLayoutY(30);
		label1.setStyle("-fx-font-size:30px; -fx-text-fill: white;");
	
		Label label2 = new Label("22-10-2016");
		label2.setLayoutX(30);
		label2.setLayoutY(65);
		label2.setStyle("-fx-font-size:24px; -fx-text-fill: white;");
	
		Label label3 = new Label("Check the release notes for more information.");
		label3.setLayoutX(30);
		label3.setLayoutY(425);
		label3.setStyle("-fx-font-size:18px; -fx-text-fill: white;");
	    		
		Button btn1 = new Button();
		btn1.setText("Play");
		btn1.setLayoutX(450);
		btn1.setLayoutY(40);
		btn1.setPrefWidth(150);
		btn1.setStyle("-fx-font-size:18px;");
		btn1.setOnAction(new EventHandler<ActionEvent>() {

			public void handle(ActionEvent event) {
				System.out.println("Play");
				page.setGame();		
				page.getGame().restart();
			}
		});
    
		Button btn2 = new Button();
		btn2.setText("High Score");
		btn2.setLayoutX(450);
		btn2.setLayoutY(90);
		btn2.setPrefWidth(150);
		btn2.setStyle("-fx-font-size:18px;");
		btn2.setOnAction(new EventHandler<ActionEvent>() {

			public void handle(ActionEvent event) {
				System.out.println("High Score");
				page.setHighScore();
			}
		});
		
		Button btn3 = new Button();
		btn3.setText("Help");
		btn3.setLayoutX(450);
		btn3.setLayoutY(140);
		btn3.setPrefWidth(150);
		btn3.setStyle("-fx-font-size:18px;");
		btn3.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				System.out.println("Help");
				page.setHelp();
			}
		});
		
		Button btn4 = new Button();
		btn4.setText("Credits");
		btn4.setLayoutX(450);
		btn4.setLayoutY(190);
		btn4.setPrefWidth(150);
		btn4.setStyle("-fx-font-size:18px;");
		btn4.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				System.out.println("Credits");
				page.setCredits();
			}
		});
		
		Button btn5 = new Button();
		btn5.setText("Release Notes");
		btn5.setLayoutX(450);
		btn5.setLayoutY(240);
		btn5.setPrefWidth(150);
		btn5.setStyle("-fx-font-size:18px;");
		btn5.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				System.out.println("Release Notes");
				page.setReleaseNotes();
			}
		});
		
		Button btn6 = new Button();
		btn6.setText("Donate");
		btn6.setLayoutX(450);
		btn6.setLayoutY(290);
		btn6.setPrefWidth(150);
		btn6.setStyle("-fx-font-size:18px;");
		btn6.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				
				System.out.println("Donate");
				page.setDonate();			
			}
		});
    
		Button btn7 = new Button();
		btn7.setText("Exit");
		btn7.setLayoutX(450);
		btn7.setLayoutY(410);
		btn7.setPrefWidth(150);
		btn7.setStyle("-fx-font-size:18px;");
		btn7.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				System.out.println("Exit");
				System.exit(0);
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
		getChildren().add(btn2);
		getChildren().add(btn3);
		getChildren().add(btn4);
		getChildren().add(btn5);
		getChildren().add(btn6);
		getChildren().add(btn7);
		
		 AnimationTimer timer1 = new AnimationTimer() {
			 
	            @Override
	            public void handle(long now) {
	            	blue1.move();
	            	blue2.move();
	            	blue3.move();
	            	blue4.move();
	            	red.move();
	            }
	        };

	        
	        timer1.start();
	}
}
