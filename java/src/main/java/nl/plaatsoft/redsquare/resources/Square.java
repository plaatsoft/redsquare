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

package nl.plaatsoft.redsquare.resources;

import org.apache.log4j.Logger;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.media.AudioClip;
import nl.plaatsoft.redsquare.tools.Constants;

public class Square extends ImageView{
	
	final static Logger log = Logger.getLogger( Square.class);
	
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
	
	public Square(Image image ,int x, int y, int dirHor, int dirVer, int step, boolean sound) {

		setImage(image);
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
			AudioClip sound = new AudioClip(getClass().getResource("/music/effect1.mp3").toExternalForm());
			sound.play();
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
