package nl.plaatsoft.redsquare.ui;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class Square extends ImageView{

	private int directionHorizontal;
	
	private int directionVertical;
	
	private double x;
	
	private double y;
	

	private int step;
	
	private double maxWidth;
	
	private double maxHeight;

	public void setPosition(double x, double y) {
		this.x=x;
		this.y=y;	
		setLayoutX(x);
		setLayoutY(y);
	}
	
	public int getStep() {
		return step;
	}

	public void setStep(int step) {
		this.step = step;
	}

	Square(String filename,int x, int y, int dirHor, int dirVer, int step, double maxWidth, double maxHeight) {		
		setImage(new Image("images/"+filename));
		this.x = x;
		this.y = y;		
		this.directionHorizontal = dirHor;
		this.directionVertical = dirVer;
		this.step = step;
		this.maxWidth = maxWidth;
		this.maxHeight = maxHeight;
		
		setLayoutX(x);
		setLayoutY(y);
	}
		
	public void move() {
	
		if (directionHorizontal==1) {
			x = x + step;			
			if (x>(maxWidth-getImage().getWidth())) {
				directionHorizontal=0;
				x=maxWidth - getImage().getWidth();
			}
		} else {
			x = x - step;
			if (x<=0) {
				directionHorizontal=1;
				x=0;
			}
		}
		
		if (directionVertical==1) {
			y = y + step;
			if (y>(maxHeight-getImage().getHeight())) {
				directionVertical=0;
				y=maxHeight - getImage().getHeight();
			}
		} else {
			y = y - step;
			if (y<=0) {
				directionVertical=1;
				y=0;
			}
		}
				
		setLayoutX(x);
		setLayoutY(y);
	}	
}
