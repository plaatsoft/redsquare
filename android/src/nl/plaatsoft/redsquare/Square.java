package nl.plaatsoft.redsquare;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.Log;

public class Square {

	private static final String TAG = "Square";
	
	private Bitmap bitmap;
	private float x;
	private float y;
	private int height;
	private int width;
	private boolean directionX;
	private boolean directionY;
	private float step;
		
	private Paint mBmpPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
	
	public void onDraw(Canvas canvas) {
		
		Rect temp = new Rect();
		temp.set(0, 0, bitmap.getWidth(), bitmap.getHeight());
		height = bitmap.getHeight();
		width = bitmap.getWidth();
		temp.offsetTo((int) x, (int) y);
		
	    canvas.drawBitmap( bitmap, null, temp, mBmpPaint);
	}
	
	public void onMove(int maxWidth, int maxHeigth ) {
		
	    if (directionX){
	        if ( x<(maxWidth-bitmap.getWidth())) {
	            x+=step;
	        } else {
	            //if (sound) QSound::play("snd/border.wav");
	            directionX=false;
	        }
	    } else {
	        if ( x>0) {
	            x-=step;
	        } else {
	            //if (sound) QSound::play("snd/border.wav");
	            directionX=true;
	        }
	    }

	    if (directionY){
	        if ( y<(maxHeigth-bitmap.getHeight())) {
	            y+=step;
	        } else {
	           //if (sound) QSound::play("snd/border.wav");
	           directionY=false;
	        }
	    } else {
	        if ( y>0) {
	            y-=step;
	        } else {
	           //if (sound) QSound::play("snd/border.wav");
	           directionY=true;
	        }
	    }	   
	}
	
	public boolean onCollision(Square red) {
		
		boolean collision=false;

	    if ((red.getX()>=x) && (red.getX()<=x+width))
	    {
	       if ((red.getY()>=y) && (red.getY()<=y+height))
	       {
	            collision = true;
	       }
	    }

	    if ((red.getX()+red.getWidth()>=x) && (red.getX()+red.getWidth()<=x+width))
	    {
	       if ((red.getY()>=y) && (red.getY()<=y+height))
	       {
	            collision = true;
	       }
	    }

	    if ((red.getX()>=x) && (red.getX()<=x+width))
	    {
	       if ((red.getY()+red.getHeight()>=y) && (red.getY()+red.getHeight()<=y+height))
	       {
	            collision = true;
	       }
	    }

	    if ((red.getX()+red.getWidth()>=x) && (red.getX()+red.getWidth()<=x+width))
	    {
	       if ((red.getY()+red.getHeight()>=y) && (red.getY()+red.getHeight()<=y+height))
	       {
	            collision = true;
	       }
	    }
	    return collision;
	}
	
	public void setBitmap(Bitmap bitmap1) {
		bitmap = bitmap1;
	}
	
	public void setX(float x1) {
		x = x1;
	}
		
	public float getX() {
		return x;
	}
	
	public void setY(float y1) {
		y = y1;
	}
	
	public float getY() {
		return y;
	}
	
	public void setStep(float step1) {
		step = step1;
	}
	
	public float getStep() {
		return step;
	}
		
	public void setDirectionX(boolean direction) {
		directionX = direction;
	}	
	
	public void setDirectionY(boolean direction) {
		directionY = direction;
	}
	
	public int getHeight() {
		return height;
	}
	
	public int getWidth() {
		return width;
	}
}
