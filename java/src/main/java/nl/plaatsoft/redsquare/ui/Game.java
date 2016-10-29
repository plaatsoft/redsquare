package nl.plaatsoft.redsquare.ui;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.TimeZone;

import org.apache.log4j.Logger;

import javafx.animation.AnimationTimer;
import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.concurrent.Task;
import javafx.event.EventHandler;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.Pane;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.paint.Color;
import javafx.util.Duration;
import nl.plaatsoft.redsquare.network.CloudScore;
import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.MyButton;
import nl.plaatsoft.redsquare.tools.MyImageView;
import nl.plaatsoft.redsquare.tools.MyLabel;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreLocal;
import nl.plaatsoft.redsquare.tools.Square;

public class Game extends Pane {

	private final static Logger log = Logger.getLogger( Game.class);
	private final static SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");
	
	private Square blue1;
	private Square blue2;
	private Square blue3;
	private Square blue4;
	private Square red;	
	
	private MyLabel label1;
	private MyLabel label2;
	private MyLabel label3;
	private ArrayList<MyImageView> list = new ArrayList<MyImageView>();

	private AnimationTimer timer1;	
	private AnimationTimer timer2;
	private int points;
	private int level;
	private boolean go = true; 
	private Date starttime;
	private Date leveltime; 
	private double offsetX=0;
	private double offsetY=0;
	
	private Task<Void> task;
	private Score score;

	private boolean collisionDetection() {
		
	    if (red.getLayoutX()<Constants.BORDER) {
	       log.info("left wall collision");
	       return true;
	    }

	    if ((red.getLayoutX()+red.getWidth())>(Constants.WIDTH-Constants.BORDER)) {
	    	 log.info("right wall collision");
	       return true;
	    }

	    if (red.getLayoutY()<Constants.BORDER) {
	    	 log.info("top wall collision");
	       return true;
	    }

	    if ((red.getLayoutY()+red.getHeight())>(Constants.HEIGHT-Constants.BORDER)) {
	    	 log.info("bottom wall collision");
	       return true;
	    }
	    
	    if (blue1.collision(red)) {
	    	log.info("collision with blue1");
	    	return true;
	    }
	    
	    if (blue2.collision(red)) {
	    	log.info("collision with blue2");
	    	return true;
	    }
	    
	    if (blue3.collision(red)) {
	    	log.info("collision with blue3");
	    	return true;
	    }
	    
	    if (blue4.collision(red)) {
	    	log.info("collision with blue4");
	    	return true;
	    }
		return false;
	}
		
	private void gameOverSound() {
		
		String path = Main.class.getResource("/music/effect2.wav").toString();
		Media media = new Media(path);
		MediaPlayer mp = new MediaPlayer(media);
		mp.play();
	}
		
	private void gameOver(final Navigator page) {
		
 	   go = false; 
 	   
 	   timer1.stop();
 	   gameOverSound();
 	   
	   getChildren().add(new MyButton(230, 380, "Exit", 18, page, page.getHome()));
  	   int y=50;
  	   getChildren().add(new MyLabel(0, y, "Game Over",60, "black"));
  	   y=y+80;
  	   getChildren().add(new MyLabel(0, y, "Play Time",30, "black"));
  	   y=y+35;
  	   getChildren().add(new MyLabel(0, y, label2.getText(),20, "black"));
  	   y=y+30;
  	   getChildren().add(new MyLabel(0, y, "Score", 30, "black"));
  	   y=y+35;
  	   getChildren().add(new MyLabel(0, y, label1.getText(),20, "black"));
  	   y=y+30;
  	  	
  	   score = new Score(starttime, points, level, "");
  	   int ranking = ScoreLocal.addScore(score);  	   
  	   
  	   if (ranking<16) {
  		   getChildren().add(new MyLabel(0, y, "You reached the "+ranking+"th place in the highscore!",28, "black"));
  	   }
  	   
  	   if (ranking<6) {
  		   y=y+40;
  		   for (int i=0; i<(6-ranking); i++) {	
  			   int x = (Constants.WIDTH/2)-((6-ranking)*64)/2;
			   MyImageView image = new MyImageView(x+(i*64),y, "images/star.png", 1);
				list.add(image);
				getChildren().add(image );
			}
  		   timer2.start();
  	   }	   			
  	   
  	   /* Sent score to cloud server */
  	   task = new Task<Void>() {
  		   public Void call() {
  			   CloudScore.set(Constants.APP_WS_NAME, Constants.APP_VERSION, score ); 
  			   return null;
  		   }
	   };
	   new Thread(task).start();
	}
	
	Game(final Navigator page) {
							
		formatter.setTimeZone(TimeZone.getTimeZone("GMT"));
		
		Image image1 = new Image("images/background1.png");
		BackgroundSize backgroundSize = new BackgroundSize(100, 100, true, true, true, false);
		BackgroundImage backgroundImage = new BackgroundImage(image1, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER, backgroundSize);
		Background background = new Background(backgroundImage);
		
		blue1 = new Square("bluesquare1.png", 1, 1, 1, 1, 1, true);
		blue2 = new Square("bluesquare2.png", 1, 1, 1, 0, 1, true);
		blue3 = new Square("bluesquare3.png", 1, 1, 0, 1, 1, true);
		blue4 = new Square("bluesquare4.png", 1, 1, 0, 0, 1, true);
		red = new Square("redsquare.png", 300, 300, 0, 0, 0, false);		
    			
		red.setOnMousePressed(new EventHandler<MouseEvent>() {
		    public void handle(MouseEvent me) {
		    	if (go) { 
		    		offsetX = me.getSceneX() - red.getPosX();
		    		offsetY = me.getSceneY() - red.getPosY();
		    	}
		    }
		});
				
		red.setOnMouseDragged(new EventHandler<MouseEvent>() {
		    public void handle(MouseEvent me) {		    	
		    	if (go) { 
		    		red.setPosition(me.getSceneX()-offsetX, me.getSceneY()-offsetY);
		    	}
		    }
		});
		
		Canvas canvas = new Canvas(Constants.WIDTH-(2*Constants.BORDER), Constants.HEIGHT-(2*Constants.BORDER));
		GraphicsContext gc = canvas.getGraphicsContext2D();
	    gc.setGlobalAlpha(0.4);
	    gc.setFill(Color.WHITE);
	    gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());    
        canvas.setLayoutX(Constants.BORDER);
        canvas.setLayoutY(Constants.BORDER);
	            	       	   
        label1 = new MyLabel(10, 5 ,""+points,18, "white");
        label2 = new MyLabel(280, 5, "00:00:00"+points, 18, "white");
        label3 = new MyLabel(620, 5, ""+level, 18, "white");
                                			
		setBackground(background);
		getChildren().add(canvas);
		getChildren().add(blue1);
		getChildren().add(blue2);    	
		getChildren().add(blue3);    	
		getChildren().add(blue4);    
		getChildren().add(red);    
		getChildren().add(label1);
		getChildren().add(label2);
		getChildren().add(label3);   	
				
		timer1 = new AnimationTimer() {
			 
	       @Override
	       public void handle(long now) {
	    	   	    	   
	    	   blue1.move();
	           blue2.move();
	           blue3.move();
	           blue4.move();
	     	           
	           points++;
	           label1.setText(""+points);
	            	
	           Date current = new Date();	            	
	           long diff1 = current.getTime() - starttime.getTime();
	           long diff2 = current.getTime() - leveltime.getTime();

	           if ( diff2>10000 ) {
	        	   leveltime = new Date(); 
	        	   level++;
	         	            	
	        	   blue1.setStep(level);
	        	   blue2.setStep(level);	
	        	   blue3.setStep(level);	
	        	   blue4.setStep(level);	
	           }
	     	           
	           label2.setText(""+formatter.format(diff1));
	           label3.setText(""+level);
	           
	           if (collisionDetection()) {
	        	   gameOver(page);
	           }
	       }
	   };	
	   
	   
	   timer2 = new AnimationTimer() {
			 
		   int rotate=0;
		   
	       @Override
	       public void handle(long now) {
	    	   	    	   
	    	   /* Rotate stars on screen */
	    	   Iterator<MyImageView> iter = list.iterator();    	
	   		   while (iter.hasNext()) {
	   			   MyImageView image = (MyImageView) iter.next();
	   			   image.setRotate(rotate++);
	   		   }
	       }
	   };	        	   
	}
	
	public void draw() {
		
		starttime = new Date();
		leveltime = new Date(); 
		points = 0;
		level = 1;
		go = true; 
		
		blue1.setPosition(1, 1);
		blue2.setPosition(Constants.WIDTH-blue2.getWidth()-1, 1);
		blue3.setPosition(1, Constants.HEIGHT-blue3.getHeight()-1);
		blue4.setPosition(Constants.WIDTH-blue4.getWidth()-1, Constants.HEIGHT-blue4.getHeight()-1);
		red.setPosition((Constants.WIDTH/2)-(red.getWidth()/2),(Constants.HEIGHT/2)-(red.getHeight()/2));
		
		blue1.setStep(level);
    	blue2.setStep(level);	
    	blue3.setStep(level);	
    	blue4.setStep(level);	
    			
		timer1.start();
	}
}
