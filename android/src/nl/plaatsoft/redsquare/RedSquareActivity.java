package nl.plaatsoft.redsquare;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.LinearLayout;
import android.widget.TextView;

public class RedSquareActivity extends Activity {
	
	private static final String TAG = "RedSquareActivity";
	private GameView mGameView;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        Log.v(TAG, "start" );
        
        mGameView = (GameView) findViewById(R.id.game_view);
        mGameView.setFocusable(true);
        mGameView.setFocusableInTouchMode(true); 
        mGameView.setStatusText((TextView) findViewById(R.id.game_text));
        
    }
}