/**
 *  @file
 *  @brief 
 *  @author wplaat
 *
 *  Copyright (C) 2008-2016 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

package nl.plaatsoft.redsquare.ui;

import javax.swing.JOptionPane;

import javafx.application.Application;
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

    	String version = System.getProperty("java.version");    
        String[] parts = version.split("_");
        if (
               ((parts[0].equals("1.7.0") && Integer.parseInt(parts[1])<70)) ||    
               ((parts[0].equals("1.8.0") && Integer.parseInt(parts[1])<100))
               )
          {   
               JOptionPane.showMessageDialog(null, "Java v"+version+" is to old. Please upgrade!");
               System.exit(1);
        }        
        launch(args);
    }
    
    
}