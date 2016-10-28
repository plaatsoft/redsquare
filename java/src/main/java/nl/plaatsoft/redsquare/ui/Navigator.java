package nl.plaatsoft.redsquare.ui;

import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import nl.plaatsoft.redsquare.tools.Constants;
import nl.plaatsoft.redsquare.tools.ScoreGlobal;

public class Navigator {
		
	private Intro1 intro1;
	private Intro2 intro2;
	private Home home;
	private Game game;	
	private Donate donate;
	private HighScore1 highScore1;
	private HighScore2 highScore2;
	private Credits credits;	
	private ReleaseNotes releaseNotes;
	private Help help;		
	private Scene scene;	
				
	Navigator() {		
		setIntro1();
		intro1.draw();
	}
	
	public void setHome() {	
		if (home==null) {
			home = new Home(this);
		}
		scene.setRoot(home);
		home.draw();
	}
	
	public void setGame() {
		/* Small hack to update content always */
		game = new Game(this);
		scene.setRoot(game);
		game.draw();
	}
	
	public void setDonate() {
		if (donate==null) {
			donate = new Donate(this);
		}
		scene.setRoot(donate);
	}
	
	public void setHighScore1() {
		ScoreGlobal.clear();
		
		/* Small hack to update content always */
		highScore1 = new HighScore1(this);
		highScore1.draw();
		scene.setRoot(highScore1);
	}
	
	public void setHighScore2() {
		/* Small hack to update content always */
		highScore2 = new HighScore2(this);
		scene.setRoot(highScore2);
	}
	
	public void setCredits() {
		if (credits==null) {
			credits = new Credits(this);
		}
		scene.setRoot(credits);
	}
	
	public void setReleaseNotes() {
		if (releaseNotes==null) {
			releaseNotes = new ReleaseNotes(this);
		}
		scene.setRoot(releaseNotes);
	}
	
	public void setHelp() {
		if (help==null) {
			help = new Help(this);
		}
		scene.setRoot(help);
	}
	
	public void setIntro1() {
		if (intro1==null) {
			intro1 = new Intro1(this);
		}
		scene = new Scene(intro1, Constants.WIDTH, Constants.HEIGHT);
		intro1.draw();
	}
	
	public void setIntro2() {
		if (intro2==null) {
			intro2 = new Intro2(this);
		}
		scene.setRoot(intro2);
		intro2.draw();
	}
	
	public void setScene(Pane object) {
		scene.setRoot(object);
	}
		
	/* ---------------------------------- */

	public Scene getScene() {
		return scene;
	}
	
	public Home getHome() {
		return home;
	}

	public Game getGame() {
		return game;
	}

	public Donate getDonate() {
		return donate;
	}

	public HighScore1 getHighScore1() {
		return highScore1;
	}
	
	public HighScore2 getHighScore2() {
		return highScore2;
	}

	public Credits getCredits() {
		return credits;
	}

	public ReleaseNotes getReleaseNotes() {
		return releaseNotes;
	}

	public Help getHelp() {
		return help;
	}

	public Intro1 getIntro1() {
		return intro1;
	}
	
	public Intro2 getIntro2() {
		return intro2;
	}
}
