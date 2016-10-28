package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.animation.AnimationTimer;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;
import nl.plaatsoft.redsquare.network.CloudVersion;
import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.Square;

public class Home extends Pane {

	final static Logger log = Logger.getLogger( Home.class);
	
	private Square blue1;
	private Square blue2;
	private Square blue3;
	private Square blue4;
	private Square red;
		
	private AnimationTimer timer;
	private MyLabel label3;
	private String upgrade;
	private Task<Void> task;
	
	Home (final Navigator page) {
		
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
	
		int step = 1;
	
		blue1 = new Square("bluesquare1.png", 30, 30, 1, 1, step);
		blue2 = new Square("bluesquare2.png", 500, 30, 1, 0, step);
		blue3 = new Square("bluesquare3.png", 30, 400, 0, 1 ,step);
		blue4 = new Square("bluesquare4.png", 500, 400, 0, 0 , step);
		red = new Square("redsquare.png", 10, 10, 0, 0, 2);
	
		MyLabel label1 = new MyLabel(30, 30, Constants.APP_NAME+" v"+Constants.APP_VERSION, 30, "white");		
		MyLabel label2 = new MyLabel(30, 70, Constants.APP_BUILD, 20, "white");
		label3 = new MyLabel(30, 420, "", 20, "white");
				
		Button btn1 = new Button();
		btn1.setText("Play");
		btn1.setLayoutX(430);
		btn1.setLayoutY(40);
		btn1.setPrefWidth(180);
		btn1.setStyle("-fx-font-size:18px;");
		btn1.setOnAction(new EventHandler<ActionEvent>() {

			public void handle(ActionEvent event) {
				page.setGame();		
			}
		});
    
		Button btn2 = new Button();
		btn2.setText("High Score");
		btn2.setLayoutX(430);
		btn2.setLayoutY(90);
		btn2.setPrefWidth(180);
		btn2.setStyle("-fx-font-size:18px;");
		btn2.setOnAction(new EventHandler<ActionEvent>() {

			public void handle(ActionEvent event) {
				page.setHighScore1();
			}
		});
		
		Button btn3 = new Button();
		btn3.setText("Help");
		btn3.setLayoutX(430);
		btn3.setLayoutY(140);
		btn3.setPrefWidth(180);
		btn3.setStyle("-fx-font-size:18px;");
		btn3.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				page.setHelp();
			}
		});
		
		Button btn4 = new Button();
		btn4.setText("Credits");
		btn4.setLayoutX(430);
		btn4.setLayoutY(190);
		btn4.setPrefWidth(180);
		btn4.setStyle("-fx-font-size:18px;");
		btn4.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				page.setCredits();
			}
		});
		
		Button btn5 = new Button();
		btn5.setText("Release Notes");
		btn5.setLayoutX(430);
		btn5.setLayoutY(240);
		btn5.setPrefWidth(180);
		btn5.setStyle("-fx-font-size:18px;");
		btn5.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				page.setReleaseNotes();
			}
		});
		
		Button btn6 = new Button();
		btn6.setText("Donate");
		btn6.setLayoutX(430);
		btn6.setLayoutY(290);
		btn6.setPrefWidth(180);
		btn6.setStyle("-fx-font-size:18px;");
		btn6.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				page.setDonate();			
			}
		});
    
		Button btn7 = new Button();
		btn7.setText("Exit");
		btn7.setLayoutX(430);
		btn7.setLayoutY(410);
		btn7.setPrefWidth(180);
		btn7.setStyle("-fx-font-size:18px;");
		btn7.setOnAction(new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent event) {
				log.info("exit");				
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
		
		timer = new AnimationTimer() {
			 
	       @Override
	       public void handle(long now) {
	          	blue1.move();
	           	blue2.move();
	           	blue3.move();
	           	blue4.move();
	           	red.move();
	            label3.setText(upgrade);
	       	}
	    };
			    
	    task = new Task<Void>() {
	        public Void call() {
	           	 upgrade = CloudVersion.check(Constants.APP_WS_NAME, Constants.APP_VERSION); 
	            return null;
	        }
		};
    }
	
	void draw() {		
		timer.start();
		new Thread(task).start();
	}
}
