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
		parameters  = "action=setScore&";
		parameters += "pid=" + CloudProduct.getPid()+ "&";
		parameters += "uid=" + CloudUser.getUid()  + "&";
		/* Remove milli seconds */
		parameters += "dt=" + (score.getTimestamp().getTime()/1000) + "&";
		parameters += "score=" + score.getScore() + "&";
		parameters += "level=" + score.getLevel();
		
		log.info(Constants.APP_WS_URL+ " "+parameters);
		String result = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		log.info(result);
	}
	
	public static void getLocal() {
		
		String parameters;
		parameters  = "action=getLocalScore&";
		parameters += "pid=" + CloudProduct.getPid() + "&";
		parameters += "uid=" + CloudUser.getUid();
		
		log.info(Constants.APP_WS_URL+ " "+parameters);
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		log.info(json);
		
		try {
			JSONArray jsonarray = new JSONArray(json);
			for (int i = 0; i < jsonarray.length(); i++) {
			    JSONObject jsonobject = jsonarray.getJSONObject(i);
			    String dt = jsonobject.getString("dt");
			    int points = jsonobject.getInt("score");
			    int level = jsonobject.getInt("level");
			    String nickname = "";
			    String country = "";
			    
			    DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			    Date date = df.parse(dt);
			    
				Score score = new Score(date, points, level, nickname, country);
			  	ScoreLocal.addScore(score);  	   
			}			
		} catch (Exception e) {
			log.error(e.getMessage());
		}
	}
	
	public static void getGlobal() {
		
		String parameters;
		parameters  = "action=getGlobalScore&";
		parameters += "pid=" + CloudProduct.getPid();
		
		log.info(Constants.APP_WS_URL+ " "+parameters);
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		log.info(json);
						
		try {
			JSONArray jsonarray = new JSONArray(json);
			for (int i = 0; i < jsonarray.length(); i++) {
			    JSONObject jsonobject = jsonarray.getJSONObject(i);
			    String dt = jsonobject.getString("dt");
			    int points = jsonobject.getInt("score");
			    int level = jsonobject.getInt("level");
			    String nickname = jsonobject.getString("nickname");
			    String country = jsonobject.getString("country");
			    			    
			    DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			    Date date = df.parse(dt);
			    
				Score score = new Score(date, points, level, nickname, country);
			  	ScoreGlobal.addScore(score);  	   
			}			
		} catch (Exception e) {
			log.error(e.getMessage());
		}
	}
}