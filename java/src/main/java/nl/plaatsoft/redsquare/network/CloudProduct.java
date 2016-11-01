package nl.plaatsoft.redsquare.network;

import org.apache.log4j.Logger;
import org.json.JSONObject;

import nl.plaatsoft.redsquare.tools.Constants;

public class CloudProduct {

	final static Logger log = Logger.getLogger( CloudProduct.class);
	
	private static int pid=0;
	
	public static void fetch() {

		String parameters = "action=getProduct"+
				"&product=" + Constants.APP_WS_NAME+
				"&version=" + Constants.APP_VERSION+
				"&os="+System.getProperty("os.name").replaceAll(" ","");
						
		log.info(Constants.APP_WS_URL+ " "+parameters);
		String json = CloudUtils.executePost(Constants.APP_WS_URL, parameters);
		log.info(json);
		
		try {
			JSONObject obj = new JSONObject(json);
			pid = obj.getInt("pid");		
		} catch (Exception e) {
			log.error(e.getMessage());
		}
	}
	
	public static int getPid() {
		if (pid==0) {
			fetch();
		}
		return pid;
	}
}
