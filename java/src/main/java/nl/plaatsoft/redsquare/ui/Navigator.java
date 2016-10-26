package nl.plaatsoft.redsquare.ui;

import javafx.scene.Scene;

public class Navigator {
	
	private Home home = new Home(this);
	private Game game = new Game(this);	
	private Donate donate = new Donate(this);
	private HighScore highScore = new HighScore(this);
	private Credits credits = new Credits(this);	
	private ReleaseNotes releaseNotes = new ReleaseNotes(this);
	private Help help = new Help(this);	
	
	public void setHelp(Help help) {
		this.help = help;
	}

	private Scene scene;	
				
	Navigator() {
		scene = new Scene(home, 640, 480);
	}
	
	public void setHome() {		
		scene.setRoot(home);
	}
	
	public void setGame() {
		scene.setRoot(game);
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
}
