package nl.plaatsoft.redsquare.ui;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.text.TextAlignment;
import nl.plaatsoft.redsquare.network.CloudUser;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.MyPanel;

public class Settings extends MyPanel {

	public Label labelSpecial(int x, int y, String value, int fontSize, String color) {
        
		Label label = new Label();
		label.setText(value);		
		label.setWrapText(true);
		label.setStyle("-fx-font-size:"+fontSize+"px; -fx-text-fill: "+color+"; ");		
		label.setMinWidth(90);
		label.setAlignment(Pos.CENTER);
		label.setTextAlignment(TextAlignment.CENTER);
		label.setLayoutX(x);
		label.setLayoutY(y);
		
		return label;
	}	
	
	private Button buttonSpecial(int x, int y, String label, int fontSize) {
	
		Button button = new Button();
		
		button.setText(label);
		button.setPrefWidth(80);
		button.setStyle("-fx-font-size:"+fontSize+"px;");	     
		    	  
		button.setLayoutX(x);
		button.setLayoutY(y);
			
		button.setOnAction(new EventHandler<ActionEvent>() { 
	       public void handle(ActionEvent event) {
	       
	       }
	    });
		
		return button;
	}
		   		  
	public void draw() {
		
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		setBackground( new Background(backgroundImage));
		
		int y=0;    
		getChildren().add (new MyLabel(0, y, "Settings", 50, "white"));		
		                
    	y+=80;    
    	getChildren().add (new MyLabel(0, y, "The nickname is used in the highscore area", 20, "white"));		
    	y+=100;   
		String nickName = CloudUser.getNickname();
		int x=50;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(0, 1).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		x+=90;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(1, 2).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		x+=90;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(2, 3).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		x+=90;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(3, 4).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		x+=90;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(4, 5).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		x+=90;
		getChildren().add(buttonSpecial(x+10,y-40,"+",20));
		getChildren().add(labelSpecial(x,y,nickName.substring(5, 6).toUpperCase(), 100, "white"));
		getChildren().add(buttonSpecial(x+10,y+140,"-",20));
		
		getChildren().add(new MyButton(230, 420, "Close", 18, Navigator.HOME));	
	}

}
