package nl.plaatsoft.redsquare.tools;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import nl.plaatsoft.redsquare.ui.Navigator;

public class MyButton extends Button {

	public MyButton(int x, int y, String value, int fontSize, final Navigator page, final Pane object) {		
		setText(value);
	    setLayoutX(x-10);
	    setLayoutY(y);
	    setPrefWidth(180);
	    setStyle("-fx-font-size:"+fontSize+"px;");	     
	    	    
	    setOnAction(new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent event) {
            	page.setScene(object);
            }
        });
	}     
}
