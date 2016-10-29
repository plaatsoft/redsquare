package nl.plaatsoft.redsquare.network;

import org.apache.log4j.Logger;
import org.json.JSONObject;

public class CloudGeoCode {

	final static Logger log = Logger.getLogger( CloudScore.class);
	
	static private String country;
	static private String city;
			
	static public void get() {
		
		String url = "http://freegeoip.net/json";
			
		log.info(url);		
		String json = CloudUtils.executeGet(url);
		log.info(json);
		
		try {
			JSONObject obj = new JSONObject(json);
			country = obj.getString("country_code");
			city = obj.getString("city");
				
		} catch (Exception e) {
			log.error(e.getMessage());
		}		
	}

	static public String getCountry() {
		
		if (country==null) {
			 get();
		}
		return country.toLowerCase();
	}

	static public String getCity() {
		if (city==null) {
			 get();
		}
		return city.toLowerCase();
	}
}
