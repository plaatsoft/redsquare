package nl.plaatsoft.redsquare.ui;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.stage.Stage;
import nl.plaatsoft.redsquare.tools.Constants;
import javafx.scene.image.Image;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Main extends Application {
	
	static MediaPlayer mp;
	
	private void music() {
		String path = getClass().getResource("/music/music.mp3").toExternalForm();
        Media media = new Media(path);
        mp = new MediaPlayer(media);
        mp.setCycleCount(MediaPlayer.INDEFINITE);
        mp.play();
	}
	
    @Override
    public void start(Stage primaryStage) {
    	    	   
    	setUserAgentStylesheet(STYLESHEET_MODENA);
    	    	
    	Navigator.go(Navigator.INTRO1);
       	     	    
        primaryStage.setTitle(Constants.APP_NAME+" v"+Constants.APP_VERSION);
        primaryStage.setScene(Navigator.getScene());
        primaryStage.sizeToScene();
        primaryStage.setResizable(false);
        primaryStage.getIcons().add(new Image("images/logo3.png"));
        primaryStage.show();
        
        music();        
    }
    
    public static void main(String[] args) {

        launch(args);
    }
    
    
}