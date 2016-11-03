package nl.plaatsoft.redsquare.tools;

import java.util.Date;

public class Score {
	
	private Date timestamp;
	private int score;
	private int level;
	private String nickname;
	private String country;
	
	public Score(Date timestamp, int score, int level, String nickname, String country) {
		this.timestamp = timestamp;
		this.score = score;
		this.level = level;
		this.nickname = nickname;
		this.country = country;
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

	public String getCountry() {
		return country;
	}

	public void setCountry(String country) {
		this.country = country;
	}
	
	public String getNickname() {
		return nickname;
	}

	public void setNickname(String nickname) {
		this.nickname = nickname;
	}
}
