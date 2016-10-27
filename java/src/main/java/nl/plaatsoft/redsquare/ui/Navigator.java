package nl.plaatsoft.redsquare.ui;

import org.apache.log4j.Logger;

import javafx.scene.Scene;
import javafx.scene.layout.Pane;

public class Navigator {
	
	final static Logger log = Logger.getLogger(  Navigator.class);
	
	private Intro1 intro1;
	private Intro2 intro2;
	private Home home;
	private Game game;	
	private Donate donate;
	private HighScore highScore;
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
		log.info("Goto home page");
		scene.setRoot(home);
		home.draw();
	}
	
	public void setGame() {
		if (game==null) {
			game = new Game(this);
		}
		log.info("Goto game page");
		scene.setRoot(game);
		game.draw();
	}
	
	public void setDonate() {
		if (donate==null) {
			donate = new Donate(this);
		}
		log.info("Goto donate page");
		scene.setRoot(donate);
	}
	
	public void setHighScore() {
		if (highScore==null) {
			highScore = new HighScore(this);
		}
		log.info("Goto highscore page");
		scene.setRoot(highScore);
	}
	
	public void setCredits() {
		if (credits==null) {
			credits = new Credits(this);
		}
		log.info("Goto credits page");
		scene.setRoot(credits);
	}
	
	public void setReleaseNotes() {
		if (releaseNotes==null) {
			releaseNotes = new ReleaseNotes(this);
		}
		log.info("Goto releaseNotes page");
		scene.setRoot(releaseNotes);
	}
	
	public void setHelp() {
		if (help==null) {
			help = new Help(this);
		}
		log.info("Goto Help page");
		scene.setRoot(help);
	}
	
	public void setIntro1() {
		if (intro1==null) {
			intro1 = new Intro1(this);
		}
		log.info("Goto intro1 page");
		scene = new Scene(intro1, 640, 480);
		intro1.draw();
	}
	
	public void setIntro2() {
		if (intro2==null) {
			intro2 = new Intro2(this);
		}
		log.info("Goto intro2 page");
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

	public HighScore getHighScore() {
		return highScore;
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
