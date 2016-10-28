package nl.plaatsoft.redsquare.tools;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class ScoreLocal {

	private static ArrayList<Score> list = new ArrayList<Score>();
		
	public static int addScore(Score score) {
		list.add(score);
		
		sort();
		
		int count = 0;
		Iterator<Score> iter = list.iterator();    	
		while (iter.hasNext()) {
			count++;
			if (score == (Score) iter.next()) {
				break;
			}
		}
		
		// Return highscore place
		return count;
	}
	
	private static void sort() {
        ScoreSort comparator = new ScoreSort();
        Collections.sort(list, comparator);
	}
	
	public static ArrayList<Score> getScore() {
		
		sort();
		return list;
	}
}
