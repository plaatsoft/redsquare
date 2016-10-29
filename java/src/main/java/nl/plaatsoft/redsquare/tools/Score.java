package nl.plaatsoft.redsquare.tools;

import java.util.Date;

public class Score {
	
	private Date timestamp;
	private int score;
	private int level;
	private String user;
	private String country;
	private String city;
	
	public Score(Date timestamp, int score, int level, String user, String country, String city) {
		this.timestamp = timestamp;
		this.score = score;
		this.level = level;
		this.user = user;
		this.country = country;
		this.city = city;
	}
	
	public Date getTimestamp() {
		return timestamp;
	}
	
	public void setTimestamp(Date timestamp) {
		this.timestamp = timestamp;
	}
	
	public int getScore() {
		return score;
	}
	
	public void setScore(int score) {
		this.score = score;
	}
	
	public int getLevel() {
		return level;
	}
	
	public void setLevel(int level) {
		this.level = level;
	}

	public String getUser() {
		return user;
	}

	public void setName(String user) {
		this.user = user;
	}

	public String getCountry() {
		return country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}	
}
