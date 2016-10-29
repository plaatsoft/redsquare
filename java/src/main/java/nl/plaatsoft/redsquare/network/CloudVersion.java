package nl.plaatsoft.redsquare.network;

import org.apache.log4j.Logger;
import org.json.JSONObject;

import nl.plaatsoft.redsquare.tools.Constants;

public class CloudVersion {
	
	final static Logger log = Logger.getLogger( CloudVersion.class);
	
	public static String check(String product, String version) {

		String returnValue="";		
		String parameters = "action=version&product=" +  product + "&version=" + version;
						
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		
		try {
			JSONObject obj = new JSONObject(json);
			String newVersion = obj.getString(product);
			if (Float.parseFloat(newVersion)>Float.parseFloat(version)) {
				returnValue = Constants.APP_NAME+" v"+newVersion+" available.";
			}
			
		} catch (Exception e) {
			log.error(e.getMessage());
		}

		return returnValue;			
	}
}
