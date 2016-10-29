package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.application.Application;
import javafx.stage.Stage;
import nl.plaatsoft.redsquare.tools.Constants;
import javafx.scene.image.Image;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Main extends Application {
	
	final static Logger log = Logger.getLogger(  Main.class);
	
	static MediaPlayer mp;
	
    @Override
    public void start(Stage primaryStage) {
    	    	
    	setUserAgentStylesheet(STYLESHEET_MODENA);
    	
    	Navigator page = new Navigator();
    	    
        primaryStage.setTitle(Constants.APP_NAME+" v"+Constants.APP_VERSION);
        primaryStage.setScene(page.getScene());
        primaryStage.sizeToScene();
        primaryStage.setResizable(false);
        primaryStage.getIcons().add(new Image("images/logo3.png"));
        primaryStage.show();
        
        String path = Main.class.getResource("/music/music.mp3").toString();
        Media media = new Media(path);
        mp = new MediaPlayer(media);
        mp.setCycleCount(MediaPlayer.INDEFINITE);
        mp.play();
    }
    
    public static void main(String[] args) {
    	
    	log.info("startup");
        launch(args);
    }
}