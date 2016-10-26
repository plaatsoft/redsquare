package nl.plaatsoft.redsquare.ui;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.image.Image;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Main extends Application {
	
    @Override
    public void start(Stage primaryStage) {
    	    	
    	Navigator page = new Navigator();
    	
    	//scene = new Scene(page.getHome(), 640, 480);
    
        primaryStage.setTitle("RedSquare v1.0");
        primaryStage.setScene(page.getScene());
        primaryStage.sizeToScene();
        primaryStage.setResizable(false);
        primaryStage.getIcons().add(new Image("images/logo3.png"));
        primaryStage.show();
        
        //String path = Main.class.getResource("/music/track1.mp3").toString();
       // Media media = new Media(path);
        //MediaPlayer mp = new MediaPlayer(media);
        //mp.play();
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}