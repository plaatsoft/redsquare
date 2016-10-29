package nl.plaatsoft.redsquare.network;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import org.apache.log4j.Logger;

import nl.plaatsoft.redsquare.tools.Constants;

public class CloudUtils {

	final static Logger log = Logger.getLogger( CloudUtils.class);
	
	public static String executeGet(String targetURL) {

		HttpURLConnection con=null;
		
		try {
			URL obj = new URL(targetURL);
			con = (HttpURLConnection) obj.openConnection();
			
			con.setRequestMethod("GET");
			con.setRequestProperty("User-Agent", Constants.APP_NAME);

			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
			String inputLine;
			StringBuffer response = new StringBuffer();
			
			while ((inputLine = in.readLine()) != null) {
				response.append(inputLine);
			}
			in.close();

			return response.toString();
		} catch (Exception e) {
			log.error(e.getMessage());
			return null;
			
		} finally {
			if (con != null) {
				con.disconnect();
			}
		}		
	}
	
	public static String executePost(String targetURL, String urlParameters) {

		log.info(targetURL+' '+urlParameters);
		
		String text="";
		HttpURLConnection connection = null;

		try {
			URL url = new URL(targetURL);
			connection = (HttpURLConnection) url.openConnection();
			connection.setRequestMethod("POST");
			connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
			connection.setRequestProperty("Content-Length", Integer.toString(urlParameters.getBytes().length));
			connection.setRequestProperty("Content-Language", "en-US");

			connection.setUseCaches(false);
			connection.setDoOutput(true);

			// Send request
			DataOutputStream wr = new DataOutputStream(connection.getOutputStream());
			wr.writeBytes(urlParameters);
			wr.close();

			// Get Response
			InputStream is = connection.getInputStream();
			BufferedReader rd = new BufferedReader(new InputStreamReader(is));
			StringBuilder response = new StringBuilder(); 
			String line;
			while ((line = rd.readLine()) != null) {
				response.append(line);
				response.append('\r');
			}
			rd.close();
			
			log.info(response.toString());			
			return response.toString();
			
		} catch (Exception e) {
			log.error(e.getMessage());
			return text;
			
		} finally {
			if (connection != null) {
				connection.disconnect();
			}
		}
	}
}
