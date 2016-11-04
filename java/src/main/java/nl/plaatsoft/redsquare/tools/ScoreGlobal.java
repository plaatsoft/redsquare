/**
 *  @file
 *  @brief 
 *  @author wplaat
 *
 *  Copyright (C) 2008-2016 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
