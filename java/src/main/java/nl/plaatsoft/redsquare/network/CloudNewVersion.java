package nl.plaatsoft.redsquare.network;

import org.apache.log4j.Logger;
import org.json.JSONObject;

import nl.plaatsoft.redsquare.tools.Constants;

public class CloudNewVersion {
	
	final static Logger log = Logger.getLogger( CloudNewVersion.class);
		
	public static String get() {

		String returnValue="";		
		String parameters = "action=getVersion&product="+Constants.APP_WS_NAME; 
						
		log.info(Constants.APP_WS_URL+ " "+parameters);
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		log.info(json);
		
		try {
			JSONObject obj = new JSONObject(json);
			String newVersion = obj.getString("product");
			if (Float.parseFloat(newVersion)>Float.parseFloat(Constants.APP_VERSION)) {
				returnValue = Constants.APP_NAME+" v"+newVersion+" available.";
			}
			
		} catch (Exception e) {
			returnValue = "No Internet connection!";
			log.error(e.getMessage());			
		}

		return returnValue;			
	}
}
