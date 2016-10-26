package nl.plaatsoft.redsquare.tools;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Date;
import java.util.Iterator;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class VersionCheck {


	
	public static String executePost(String targetURL, String product, String version) {

		HttpURLConnection connection = null;
		String urlParameters = "product=" + product + "&version=" + version;

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
			
			return checkVersion(response.toString(), product, version);
			
		} catch (Exception e) {
			e.printStackTrace();
			return null;
			
		} finally {
			if (connection != null) {
				connection.disconnect();
			}
		}
	}

	private static String checkVersion(String json, String product, String currentVersion) {

		try {
			JSONParser parser = new JSONParser();
			Object obj = parser.parse(json);

			JSONObject jsonObject = (JSONObject) obj;
			float newVersion = Float.parseFloat((String) jsonObject.get(product));
			float tmp = Float.parseFloat(currentVersion);
			
			if (newVersion>tmp) {
				return "RedSquare v"+newVersion+" available.";
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}
