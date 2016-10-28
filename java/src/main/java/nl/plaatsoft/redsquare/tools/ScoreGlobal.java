package nl.plaatsoft.redsquare.tools;

import java.util.ArrayList;
import java.util.Iterator;

import org.apache.log4j.Logger;

public class ScoreGlobal {

	final static Logger log = Logger.getLogger(  ScoreGlobal.class);
	
	private static ArrayList<Score> list = new ArrayList<Score>();
		
	public static void addScore(Score score) {
		list.add(score);
	}
		
	public static ArrayList<Score> getScore() {
		
		return list;
	}
	
	public static void clear() {
		
		log.info("enter");
		Iterator<Score> iter = list.iterator();    	
		while (iter.hasNext()) {
			Score score = (Score) iter.next();
			iter.remove();
		}
		log.info("leave");
	}
}
