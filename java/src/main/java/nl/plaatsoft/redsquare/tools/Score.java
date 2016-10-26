package nl.plaatsoft.redsquare.tools;

import java.util.Date;

public class Score {
	
	private Date timestamp;
	private Integer score;
	private Integer level;
	
	public Score(Date timestamp, Integer score, Integer level) {
		super();
		this.timestamp = timestamp;
		this.score = score;
		this.level = level;
	}
	
	public Date getTimestamp() {
		return timestamp;
	}
	
	public void setTimestamp(Date timestamp) {
		this.timestamp = timestamp;
	}
	
	public Integer getScore() {
		return score;
	}
	
	public void setScore(Integer score) {
		this.score = score;
	}
	
	public Integer getLevel() {
		return level;
	}
	
	public void setLevel(Integer level) {
		this.level = level;
	}
	
	
}
