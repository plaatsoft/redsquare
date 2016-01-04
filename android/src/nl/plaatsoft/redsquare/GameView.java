package nl.plaatsoft.redsquare;

import java.util.Random;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

public class GameView extends View {

	private static final String TAG = "GameView";
		
	private static final int MAX_SQUARES = 4; 
	private static final int INIT_STEP = 1;
    private static final int PAUSE = 0;
    private static final int READY = 1;
    private static final int RUNNING = 2;
    private static final int LOSE = 3;
    
    private long mMoveDelay = 10;
    private long mLastMove;
    private long mScore = 0;
    private int mMode = READY;
    private TextView mStatusText;
	private Drawable mDrawableBg;
	private Square red; 	
	private Square[] blue = new Square[4];
    private RefreshHandler mRedrawHandler = new RefreshHandler();

	// -----------------------------------------
	// INITS
	// -----------------------------------------
    
    private void initBackground() {
    	
    	Log.v(TAG, "initBackground - enter" );
    	 
    	// Create background
        mDrawableBg = getResources().getDrawable(R.drawable.gameboard);
        setBackgroundDrawable(mDrawableBg);
       
        Log.v(TAG, "initBackground - leave" );
    }
    
	private void initGame() {
		
		Log.v(TAG, "initSquares - enter" );
			 
		mScore=0;
		
		Random random = new Random();

		red = new Square();		
		red.setBitmap(getResBitmap(R.drawable.redsquare));
		red.setX(360);
		red.setY(160);    
			
		blue[0] = new Square();
		int x = random.nextInt(800);
		int y = random.nextInt(400);
      	blue[0].setBitmap(getResBitmap(R.drawable.bluesquare1));
      	blue[0].setX(x);
		blue[0].setY(y);
		blue[0].setDirectionX(true);
		blue[0].setDirectionY(true);
		blue[0].setStep(INIT_STEP);
		
		blue[1] = new Square();
		x = random.nextInt(800);
		y = random.nextInt(400);
      	blue[1].setBitmap(getResBitmap(R.drawable.bluesquare2));
      	blue[1].setX(x);
		blue[1].setY(y);
		blue[1].setDirectionY(true);
		blue[1].setDirectionX(false);
		blue[1].setStep(INIT_STEP);
		
		blue[2] = new Square();
		x = random.nextInt(800);
		y = random.nextInt(400);
      	blue[2].setBitmap(getResBitmap(R.drawable.bluesquare3));
      	blue[2].setX(x);
		blue[2].setY(y);
		blue[2].setDirectionY(false);
		blue[2].setDirectionX(true);
		blue[2].setStep(INIT_STEP);
		
		blue[3] = new Square();
		x = random.nextInt(800);
		y = random.nextInt(400);
      	blue[3].setBitmap(getResBitmap(R.drawable.bluesquare4));
      	blue[3].setX(x);
		blue[3].setY(y);
		blue[3].setDirectionY(false);
		blue[3].setDirectionX(false);
		blue[3].setStep(INIT_STEP);
		
		Log.v(TAG, "initSquares - leave" );
	}

	// -----------------------------------------
	// CONTRUCTORS
	// -----------------------------------------
	    
	public GameView(Context context, AttributeSet attrs) {
		super(context, attrs);
	                  
		initBackground();
		initGame();
		setMode(mMode);
		setFocusable(true);
	}
		
	public GameView(Context context, AttributeSet attrs, int defStyle) {
	    super(context, attrs, defStyle);
		    
	    initBackground();
	    initGame();
	    setMode(mMode);
	    setFocusable(true);
	}
			
	// -----------------------------------------
	// HANDLER 
	// -----------------------------------------

    class RefreshHandler extends Handler {

        @Override
        public void handleMessage(Message msg) {
  
            GameView.this.update();
            GameView.this.invalidate();
        }

        public void sleep(long delayMillis) {
        	this.removeMessages(0);
            sendMessageDelayed(obtainMessage(0), delayMillis);
        }
    }
   
    /**
     * Handles the basic update loop, checking to see if we are in the running
     * state, determining if a move should be made, updating the snake's location.
     */
    public void update() {
    	if (mMode == RUNNING) {
    	
    		long now = System.currentTimeMillis();

    		if (now - mLastMove > mMoveDelay) {
            
    			mScore++;
				
    			for (int i=0; i<MAX_SQUARES; i++) {			  	 		   
    				blue[i].onMove(this.getWidth(), this.getHeight());
    				if (mScore%100==0) {
    					// Increase step every 100 frames.
    					blue[i].setStep(blue[i].getStep()+ 0.2F);
    				}    				
    			}	
    			mLastMove = now;
    		}
    		mRedrawHandler.sleep(mMoveDelay);
    	}
    }
    
    // -----------------------------------------
 	// OTHER
 	// -----------------------------------------
 	  
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent msg) {

        if (keyCode == KeyEvent.KEYCODE_SEARCH) {
            if (mMode == READY | mMode == LOSE) {

                setMode(RUNNING);
                update();
                return (true);
            }

            if (mMode == PAUSE) {

                setMode(RUNNING);
                update();
                return (true);
            }
            return (true);
        }
        return super.onKeyDown(keyCode, msg);
    }        

    @Override 
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        boolean mCurDown = action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_MOVE;
        if (mCurDown) {
        	red.setX((int) event.getX()-15);
        	red.setY((int) event.getY()-15);
        }
        return true;
    }

    
    public void setMode(int newMode) {
       int oldMode = mMode;
       mMode = newMode;

       if (mStatusText==null) return;
       
       if (newMode == RUNNING & oldMode != RUNNING) {
            mStatusText.setVisibility(View.INVISIBLE);
            update();
            return;
       }

       Resources res = getContext().getResources();
       CharSequence str = "";
       if (newMode == PAUSE) {
            str = res.getText(R.string.mode_pause);
       }
       if (newMode == READY) {
           str = res.getText(R.string.mode_ready);
       }
       if (newMode == LOSE) {
           str = res.getString(R.string.mode_lose_prefix) + mScore
               + res.getString(R.string.mode_lose_suffix);
       }
       mStatusText.setText(str);
       mStatusText.setVisibility(View.VISIBLE);
    }
            
    public void setStatusText(TextView tmp) {
    	
    	mStatusText= tmp;
    }
    
	@Override
	protected void onDraw(Canvas canvas) {
	   super.onDraw(canvas);

	   red.onDraw(canvas);
	             
	   for (int i=0; i<MAX_SQUARES; i++) {			  	 		   
		   blue[i].onDraw(canvas);	
		   if ( blue[i].onCollision(red) ) {
			   setMode(LOSE);
		   }
       }	
	}  
	 
	private Bitmap getResBitmap(int bmpResId) {
        Options opts = new Options();
        opts.inDither = false;

        Resources res = getResources();
        Bitmap bmp = BitmapFactory.decodeResource(res, bmpResId, opts);

        if (bmp == null && isInEditMode()) {
        	
            // BitmapFactory.decodeResource doesn't work from the rendering
            // library in Eclipse's Graphical Layout Editor. Use this workaround instead.
            Drawable d = res.getDrawable(bmpResId);
            int w = d.getIntrinsicWidth();
            int h = d.getIntrinsicHeight();
            bmp = Bitmap.createBitmap(w, h, Config.ARGB_8888);
            Canvas c = new Canvas(bmp);
            d.setBounds(0, 0, w - 1, h - 1);
            d.draw(c);
        }

        return bmp;
    }
	
	// -----------------------------------------
	// THE END
	// -----------------------------------------
}
