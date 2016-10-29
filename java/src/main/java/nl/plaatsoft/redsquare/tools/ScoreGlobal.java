package nl.plaatsoft.redsquare.tools;

import java.util.ArrayList;
import java.util.Iterator;

public class ScoreGlobal {

	private static ArrayList<Score> list = new ArrayList<Score>();
		
	public static void addScore(Score score) {
		list.add(score);
	}
		
	public static ArrayList<Score> getScore() {
		
		return list;
	}
	
	public static void clear() {
		
		Iterator<Score> iter = list.iterator();    	
		while (iter.hasNext()) {
			Score score = (Score) iter.next();
			iter.remove();
		}
	}
}
