package nl.plaatsoft.redsquare.tools;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Square extends ImageView{
	
	private int directionHorizontal;
	private int directionVertical;
	private double x;
	private double y;
	private double width;
	private double height;
	private int step;
	private boolean sound;
	
	public void setPosition(double x, double y) {
		
		this.x=x;
		this.y=y;	
		
		setLayoutX(x);
		setLayoutY(y);
	}

	public Square(String filename,int x, int y, int dirHor, int dirVer, int step, boolean sound) {

		setImage(new Image("images/"+filename));
		this.x = x;
		this.y = y;		
		this.width = getImage().getWidth();
		this.height = getImage().getHeight();
		this.directionHorizontal = dirHor;
		this.directionVertical = dirVer;
		this.step = step;
		this.sound = sound;
		
		setLayoutX(x);
		setLayoutY(y);
	}
		
	private void collisionSound() {
		
		if (sound) {
			String path = Square.class.getResource("/music/effect1.wav").toString();
			Media media = new Media(path);
			MediaPlayer mp = new MediaPlayer(media);
			mp.play();
		}
	}
	
	public void move() {
			
		if (directionHorizontal==1) {
			x += step;			
			if (x>(Constants.WIDTH-width)) {
				directionHorizontal=0;
				x = Constants.WIDTH - width;
				collisionSound();
			}
		} else {
			x -= step;
			if (x<=0) {
				directionHorizontal=1;
				x=0;
				collisionSound();
			}
		}
		
		if (directionVertical==1) {
			y += step;
			if (y>(Constants.HEIGHT-height)) {
				directionVertical=0;
				y=Constants.HEIGHT - height;
				collisionSound();
			}
		} else {
			y -= step;
			if (y<=0) {
				directionVertical=1;
				collisionSound();
				y=0;
			}
		}

		setLayoutX(x);
		setLayoutY(y);
	}	
	
	public boolean collision(Square red) {
		
	    boolean collision=false;
	    
	    if (red.getPosX() < x + width &&  red.getPosX() + red.getWidth() > x &&
	    	red.getPosY() < y + height && red.getHeight() + red.getPosY() > y) {
	    	collision = true;
	  	}
	    return collision;
	}	
	
	public int getStep() {
		return step;
	}

	public void setStep(int step) {
		this.step = step;
	}
	
	public int getPosX() {		
		return (int) x;
	}
	
	public int getPosY() {		
		return (int) y;
	}
	
	public int getWidth() {		
		return (int) width;
	}
	
	public int getHeight() {		
		return (int) height;		
	}
}
