package nl.plaatsoft.redsquare.network;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.log4j.Logger;
import org.json.JSONArray;
import org.json.JSONObject;

import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.Score;
import nl.plaatsoft.redsquare.tools.ScoreGlobal;
import nl.plaatsoft.redsquare.tools.ScoreLocal;

public class CloudScore {

final static Logger log = Logger.getLogger( CloudScore.class);
	
	public static void set(String product, String version, Score score) {
									
		String parameters;
		parameters  = "action=setLocal&";
		parameters += "product=" + Constants.APP_WS_NAME + "&";
		parameters += "version=" + version  + "&";
		/* Remove milli seconds */
		parameters += "dt=" + (score.getTimestamp().getTime()/1000) + "&";
		parameters += "score=" + score.getScore() + "&";
		parameters += "level=" + score.getLevel() + "&";
		parameters += "user="+System.getProperty("user.name") + "&";
		parameters += "os="+System.getProperty("os.name").replaceAll(" ","");
		
		log.info("enter ["+parameters+"]");
		
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		
		log.info("leave ["+json+"]" );
	}
	
	public static void getLocal(String product, String version) {
		
		String parameters;
		parameters  = "action=getLocal&";
		parameters += "product=" + Constants.APP_WS_NAME + "&";
		parameters += "user="+System.getProperty("user.name") + "&";
		parameters += "os="+System.getProperty("os.name").replaceAll(" ","");

		log.info("enter ["+parameters+"]");
		
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
						
		try {
			JSONArray jsonarray = new JSONArray(json);
			for (int i = 0; i < jsonarray.length(); i++) {
			    JSONObject jsonobject = jsonarray.getJSONObject(i);
			    String dt = jsonobject.getString("dt");
			    int points = jsonobject.getInt("score");
			    int level = jsonobject.getInt("level");
			    String user = jsonobject.getString("user");
			    
			    DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			    Date date = df.parse(dt);
			    
				Score score = new Score(date, points, level, user);
			  	ScoreLocal.addScore(score);  	   
			}			
		} catch (Exception e) {
			log.error(e.getMessage());
		}
	}
	
	public static void getGlobal(String product, String version) {
		
		String parameters;
		parameters  = "action=getGlobal&";
		parameters += "product=" + Constants.APP_WS_NAME + "&";
		parameters += "user="+System.getProperty("user.name") + "&";
		parameters += "os="+System.getProperty("os.name").replaceAll(" ","");

		log.info("enter ["+parameters+"]");
		
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
						
		try {
			JSONArray jsonarray = new JSONArray(json);
			for (int i = 0; i < jsonarray.length(); i++) {
			    JSONObject jsonobject = jsonarray.getJSONObject(i);
			    String dt = jsonobject.getString("dt");
			    int points = jsonobject.getInt("score");
			    int level = jsonobject.getInt("level");
			    String user = jsonobject.getString("user");
			    
			    DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			    Date date = df.parse(dt);
			    
				Score score = new Score(date, points, level, user);
			  	ScoreGlobal.addScore(score);  	   
			}			
		} catch (Exception e) {
			log.error(e.getMessage());
		}
	}
}