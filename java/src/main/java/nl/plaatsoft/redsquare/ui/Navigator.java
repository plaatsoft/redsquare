package nl.plaatsoft.redsquare.ui;

import javafx.scene.Scene;

public class Navigator {
	
	private Intro1 intro1 = new Intro1(this);
	private Intro2 intro2 = new Intro2(this);
	private Home home = new Home(this);
	private Game game = new Game(this);	
	private Donate donate = new Donate(this);
	private HighScore highScore = new HighScore(this);
	private Credits credits = new Credits(this);	
	private ReleaseNotes releaseNotes = new ReleaseNotes(this);
	private Help help = new Help(this);		
	private Scene scene;	
				
	Navigator() {
		scene = new Scene(intro1, 640, 480);
		intro1.draw();
	}
	
	public void setHome() {		
		scene.setRoot(home);
		home.draw();
	}
	
	public void setGame() {
		scene.setRoot(game);
		game.draw();
	}
	
	public void setDonate() {
		scene.setRoot(donate);
	}
	
	public void setHighScore() {
		scene.setRoot(highScore);
	}
	
	public void setCredits() {
		scene.setRoot(credits);
	}
	
	public void setReleaseNotes() {
		scene.setRoot(releaseNotes);
	}
	
	public void setHelp() {
		scene.setRoot(help);
	}
	
	public void setIntro1() {
		scene.setRoot(intro1);
		intro1.draw();
	}
	
	public void setIntro2() {
		scene.setRoot(intro2);
		intro2.draw();
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
