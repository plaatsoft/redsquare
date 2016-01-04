package nl.plaatsoft.redsquare;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class CreditsActivity extends Activity {

	@Override
	public void onCreate(Bundle bundle) {
		super.onCreate(bundle);
		setContentView(R.layout.credits);
		Bundle extras = getIntent().getExtras();
		if (extras == null) {
			return;
		}
		//String value1 = extras.getString("Value1");
		//String value2 = extras.getString("Value2");
		/*if (value1 != null && value2 != null) {
			EditText text1 = (EditText) findViewById(R.id.EditText01);
			EditText text2 = (EditText) findViewById(R.id.EditText02);
			text1.setText(value1);
			text2.setText(value2);
		}*/
	}

	public void onClick(View view) {
			finish();
	}

	@Override
	public void finish() {
		Intent data = new Intent();
		data.putExtra("returnKey1", "Swinging on a star. ");
		data.putExtra("returnKey2", "You could be better then you are. ");
		setResult(RESULT_OK, data);
		super.finish();
	}		
}
