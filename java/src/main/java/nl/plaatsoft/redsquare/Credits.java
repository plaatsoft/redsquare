package nl.plaatsoft.redsquare;

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

public class Credits extends Pane {

	Credits(final Navigator page) {
		
		Image image1 = new Image("images/background.png");
    	BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
    	BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
    	Background background = new Background(backgroundImage);
    	    	
		Label label1 = new Label("Credits");
		label1.setLayoutX(30);
		label1.setLayoutY(30);
		label1.setStyle("-fx-font-size:30px; -fx-text-fill: white;");
		
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
		getChildren().add(btn1);
	}

}
