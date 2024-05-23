// Welcome to Zombie Arena Variation!
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include "Obstacle.h"

using namespace sf;

int main()
{
	// Here is the instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),"Zombie Arena", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(mainView);

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = NULL;

	// Setting up bullet 1 and 2 
	Bullet bullets[100];
	int currentBullet = 0;
	int secondBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	bool multi_shot = false;
	// When was the fire button last pressed?
	Time lastPressed;

	
	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// Create pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);
	Pickup speedPickup(3);
	Pickup scorePickup(4);
	Pickup negative_scorePickup(5);
	Pickup multi_shotPickup(6);

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/background.jpg");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Scaling the background to size
	float scaleFactor = 1.0f;
	spriteGameOver.setScale(scaleFactor, scaleFactor);

	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);


	// Load the font
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

	// Zombie Arena Title
	Text titleText;
	titleText.setFont(font);
	titleText.setCharacterSize(160);
	titleText.setFillColor(Color::Red);
	titleText.setPosition(250, 150);
	titleText.setString("Game 3: Zombie Arena");

	// Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::Red);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");


	// Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::Green);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");

	// Levelling up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::Red);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::Red);
	ammoText.setPosition(200, 980);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::Red);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// High Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::Green);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::Green);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");

	// Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::Green);
	waveNumberText.setPosition(1250, 980);
	waveNumberText.setString("Wave: 0");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);
		
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// Prepare the backgroud gameplay music
	SoundBuffer main_musicBuffer;
	main_musicBuffer.loadFromFile("sound/mainmenu_music.mp3");
	Sound main_music;
	main_music.setBuffer(main_musicBuffer);
	bool ismain_musicPlaying = false;

	// Prepare the paused music
	SoundBuffer paused_musicBuffer;
	paused_musicBuffer.loadFromFile("sound/paused_music.mp3");
	Sound paused_music;
	paused_music.setBuffer(paused_musicBuffer);
	bool ispaused_musicPlaying = false;

	// Zombie death sound
	SoundBuffer zombie_deathBuffer;
	zombie_deathBuffer.loadFromFile("sound/zombie_death.mp3");
	Sound zombie_death;
	zombie_death.setBuffer(zombie_deathBuffer);

	// Player death and half health sound
	SoundBuffer player_deathBuffer;
	player_deathBuffer.loadFromFile("sound/player_death.mp3");
	Sound player_death;
	player_death.setBuffer(player_deathBuffer);

	// Speed pickup sound
	SoundBuffer speed_pickupBuffer;
	speed_pickupBuffer.loadFromFile("sound/speed_pickup.wav");
	Sound speed_pickup;
	speed_pickup.setBuffer(speed_pickupBuffer);

	// Postive score sound
	SoundBuffer postive_scoreBuffer;
	postive_scoreBuffer.loadFromFile("sound/postive_score.wav");
	Sound postive_score;
	postive_score.setBuffer(postive_scoreBuffer);

	// Negative score sound
	SoundBuffer negative_scoreBuffer;
	negative_scoreBuffer.loadFromFile("sound/negative_score.wav");
	Sound negative_score;
	negative_score.setBuffer(negative_scoreBuffer);

	// Multi shot pickup sound
	SoundBuffer multishotBuffer;
	multishotBuffer.loadFromFile("sound/multishot_pickup.mp3");
	Sound multishot;
	multishot.setBuffer(multishotBuffer);

	// Creating obstacles
	std::vector<obstacle> obstacles;

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
					
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{

					state = State::LEVELING_UP;
					wave = 0;
					score = 0;

					// Prepare the gun and ammo for next game
					currentBullet = 0;
					bulletsSpare = 24;
					bulletsInClip = 6;
					clipSize = 6;
					fireRate = 1;

					// Reset multi-shot power-up
					multi_shot = false; 

					// Reset the player's stats
					player.resetPlayerStats();

					
				}
			
				
				if (state == State::PLAYING)
				{

					// Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							// Plenty of bullets. Reload.
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;		
							reload.play();
						}
						else if (bulletsSpare > 0)
						{
							// Only few bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;				
							reload.play();
						}
						else
						{
							// More here soon?!
							reloadFailed.play();
						}
					}
				}

			}
		}// End event polling

		// Handling the music
		// Playing music 
		if (state == State::PLAYING)
		{
			if (!ismain_musicPlaying)
			{
				// Play main menu music
				main_music.setLoop(true);
				main_music.play();
				ismain_musicPlaying = true;
			}
		}
		else
		{
			// Stop main menu music when not in the LEVELING_UP state
			if (ismain_musicPlaying)
			{

				main_music.stop();
				ismain_musicPlaying = false;
			}
		}
		// Leveling up/ Main menu music
		if (state == State::LEVELING_UP || state == State::GAME_OVER)
		{
			if (!ispaused_musicPlaying)
			{
				// Set the music to loop and play it
				paused_music.setLoop(true);
				paused_music.play();
				ispaused_musicPlaying = true;
			}
		}
		else
		{
			// Stop main menu music
			if (ispaused_musicPlaying)
			{
				// Stop the music
				paused_music.stop();
				ispaused_musicPlaying = false;
			}
		}


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// Shoot One bullet like normal
				if (gameTimeTotal.asMilliseconds()- lastPressed.asMilliseconds()> 1000 / fireRate && bulletsInClip > 0)
				{
					// if multi-shot isn't picked up
					if (!multi_shot)
					{ 
					// Pass the center of the player and the center of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
					}
				}
				// Multi Shot
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
				{
					// if the player picks up the multi-shot pickup
					if(multi_shot)
					{
						// Create the first bullet
						bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
						currentBullet++;

						if (currentBullet > 99)
						{
							currentBullet = 0;
						}
						// Lose a bullet
						bulletsInClip--;
						// Create the second bullet
						bullets[secondBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.x);
						currentBullet++;

						if (currentBullet > 99)
						{
							currentBullet = 0;
						}

						lastPressed = gameTimeTotal;
						shoot.play();
						// Lose a second bullet
						bulletsInClip--;
					}
				}

			}// End fire a bullet

		}// End WASD while playing

		// Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			// Just reset player stats again to make sure they are defult
			player.resetPlayerStats();

			// Handle the player levelling up
			if (event.key.code == Keyboard::Num1)
			{
				// Increase fire rate
				fireRate++;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				// Increase clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				// Increase health
				player.upgradeHealth();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				// Increase speed
				player.upgradeSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				// Increase Health
				healthPickup.upgrade();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				// More Ammo Pickups
				ammoPickup.upgrade();
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Increase the wave number
				wave++;

				// Prepare thelevel
				// We will modify the next two lines later
				arena.width = 500 * wave;
				arena.height = 500 * wave;
				arena.left = 0;
				arena.top = 0;

				// Pass the vertex array by reference 
				// to the createBackground function
				int tileSize = createBackground(background, arena);

				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pick-ups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);
				speedPickup.setArena(arena);
				scorePickup.setArena(arena);
				negative_scorePickup.setArena(arena);
				multi_shotPickup.setArena(arena);

				// Configuring the obstacles 
				for (int i = 0; i < 5; i++) 
				{ 
					obstacle newObstacle;
					newObstacle.spawn(arena, resolution, tileSize, obstacles);
					obstacles.push_back(newObstacle);
				}

				// Create a horde of zombies
				numZombies = 5 * wave;

				// Delete the previously allocated memory (if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				// Play the powerup sound
				powerup.play();

				multi_shot = false; // Reset multi-shot power-up

				// Reset the clock so there isn't a frame jump
				clock.restart();

				window.setView(mainView);

			}
			

		}// End levelling up

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition(), obstacles);

			// Make a note of the players new position
			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player				
			mainView.setCenter(player.getCenter());

			// Loop through each Zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition, obstacles);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);
			speedPickup.update(dtAsSeconds);
			scorePickup.update(dtAsSeconds);
			negative_scorePickup.update(dtAsSeconds);
			multi_shotPickup.update(dtAsSeconds);

			// Collision detection
			// Have any zombies been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() && 
						zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects
							(zombies[j].getPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was a kill
							if (zombies[j].hit()) {
								// Not just a hit but a kill too
								score += 10;
								if (score >= hiScore)
								{
									hiScore = score;
								}

								numZombiesAlive--;
								
								// Zombie death sound
								zombie_death.play();

								// When all the zombies are dead (again)
								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}
							}	

							// Make a splat sound
							splat.play();
							
						}
					}

				}
			}// End zombie being shot

			// Have any zombies touched the player			
			for (int i = 0; i < numZombies; i++)
			{
				if (player.getPosition().intersects
					(zombies[i].getPosition()) && zombies[i].isAlive())
				{

					if (player.hit(gameTimeTotal))
					{
						// More here later
						hit.play();

					}
					if (player.getHealth() == 50)
					{
						// Play half health sound
						player_death.play();

					}


					if (player.getHealth() <= 0)
					{
						state = State::GAME_OVER;

						// Outputing the High Score
						std::ofstream outputFile("gamedata/scores.txt");
						outputFile << hiScore;
						outputFile.close();

						// Player Death sound
						player_death.play();
						
					}
				}
			}// End player touched


			// Has the player touched health pickup
			if (player.getPosition().intersects
				(healthPickup.getPosition()) && healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
				// Play a sound
				pickup.play();
				
			}

			// Has the player touched ammo pickup
			if (player.getPosition().intersects
				(ammoPickup.getPosition()) && ammoPickup.isSpawned())
			{
				// Ammo Pickup
				bulletsSpare += ammoPickup.gotIt();
				// Play a sound
				reload.play();
				
			}

			// Has the player touched speed pickup
			if (player.getPosition().intersects
			(speedPickup.getPosition()) && speedPickup.isSpawned())
			{
				// Increase Speed
				player.increaseSpeedLevel(speedPickup.gotIt());
				// Play a sound
				speed_pickup.play();

			}

			// Has the player touched score pickup
			if (player.getPosition().intersects
			(scorePickup.getPosition()) && scorePickup.isSpawned())
			{
				// Double Score
				score *= 2 * scorePickup.gotIt();
				
				// Play a sound
				postive_score.play();
			}

			// Has the player touched negative score pickup
			if (player.getPosition().intersects
			(negative_scorePickup.getPosition()) && negative_scorePickup.isSpawned())
			{
				// Half the score
				score /= 2 * negative_scorePickup.gotIt();

				// Play a sound
				negative_score.play();
			}

			// Has the player touched multi-shot pickup
			if (player.getPosition().intersects
			(multi_shotPickup.getPosition()) && multi_shotPickup.isSpawned())
			{
				// Multi-shot is now enabled
				multi_shot = true & multi_shotPickup.gotIt();

				// Play a sound
				multishot.play();
			}

			// size up the health bar
			healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

			// Increment the amount of time since the last HUD update
			timeSinceLastUpdate += dt;
			// Increment the number of frames since the last HUD calculation
			framesSinceLastHUDUpdate++;
			// Calculate FPS every fpsMeasurementFrameInterval frames
			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
			{

				// Update game HUD text
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;

				// Update the ammo text
				ssAmmo << bulletsInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				// Update the score text
				ssScore << "Score:" << score;
				scoreText.setString(ssScore.str());

				// Update the high score text
				ssHiScore << "Hi Score:" << hiScore;
				hiScoreText.setString(ssHiScore.str());

				// Update the wave
				ssWave << "Wave:" << wave;
				waveNumberText.setString(ssWave.str());

				// Update the high score text
				ssZombiesAlive << "Zombies:" << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

				framesSinceLastHUDUpdate = 0;
				timeSinceLastUpdate = Time::Zero;
			}// End HUD update

		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
		
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);
			// Draw the zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the obstacle
			for (const obstacle& obs : obstacles)
			{
				window.draw(obs.getSprite());
			}


			// Draw the pickups is currently spawned
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}
			if (speedPickup.isSpawned())
			{
				window.draw(speedPickup.getSprite());
			}
			if (scorePickup.isSpawned())
			{
				window.draw(scorePickup.getSprite());
			}
			if (negative_scorePickup.isSpawned())
			{
				window.draw(negative_scorePickup.getSprite());
			}
			if (multi_shotPickup.isSpawned())
			{
				window.draw(multi_shotPickup.getSprite());
			}

			//Draw the crosshair
			window.draw(spriteCrosshair);

			// Switch to the HUD view
			window.setView(hudView);

			// Draw all the HUD elements
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);

		}

		if (state == State::LEVELING_UP)
		{
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
			window.draw(titleText);
		}

		if (state == State::GAME_OVER)
		{
			
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(titleText);
		}

		window.display();

	}// End game loop

	return 0;
}