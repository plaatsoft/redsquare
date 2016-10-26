package nl.plaatsoft.redsquare.ui;

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
import nl.plaatsoft.redsquare.tools.MyLabel;

public class Donate extends Pane {

	Donate(final Navigator page) {
		
		Image image1 = new Image("images/background1.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	
    	int y=60;
    	MyLabel label1 = new MyLabel(230, 20, "Donate", 60);
    	y+=60;
    	MyLabel label2 = new MyLabel(90, y, "If you enjoy this game, please sent me a", 26);
    	y+=30;
    	MyLabel label3 = new MyLabel(80, y, "small donation. You can make a donation", 26);
    	y+=30;
    	MyLabel label4 = new MyLabel(50, y, "online with your credit card, or PayPal account.", 26);
    	y+=30;    	 
    	MyLabel label5 = new MyLabel(50, y, "Your credit card will be processed by PayPal, a", 26);
    	y+=30;
    	MyLabel label6 = new MyLabel(70, y, "trusted name in secure online transactions.", 26);
    	y+=60;
    	MyLabel label7 = new MyLabel(80, y, "Please visit http://www.plaatsoft.nl/donate", 26);
    	y+=30;
    	MyLabel label8 = new MyLabel(30, y, "Click on the donate link and follow the instructions", 26);
    	       		
		Button btn1 = new Button();
        btn1.setText("Close");
        btn1.setLayoutX(250);
        btn1.setLayoutY(420);
        btn1.setPrefWidth(150);
        btn1.setStyle("-fx-font-size:18px;");
        btn1.setOnAction(new EventHandler<ActionEvent>() {
 
            public void handle(ActionEvent event) {
            	page.setHome();
            }
        });
                
		setBackground(background);
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(label3);
		getChildren().add(label4);
		getChildren().add(label5);
		getChildren().add(label6);
		getChildren().add(label7);
		getChildren().add(label8);		
		getChildren().add(btn1);
	}
	
}
