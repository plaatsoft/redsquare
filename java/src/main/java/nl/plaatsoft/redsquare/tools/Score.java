package nl.plaatsoft.redsquare.tools;

import java.util.Date;

public class Score {
	
	private Date timestamp;
	private int score;
	private int level;
	private String user;
	
	public Score(Date timestamp, int score, int level, String user) {
		this.timestamp = timestamp;
		this.score = score;
		this.level = level;
		this.user = user;
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
}
