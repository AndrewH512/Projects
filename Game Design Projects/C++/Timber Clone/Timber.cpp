// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// Function declaration
void updateApples(int seed, float elapsedTime, int playerDeaths);

// Setting the Score
int score = 0;

// Setting up the apples
const int NUM_APPLES = 6;
Sprite apple[NUM_APPLES];

// Where is the player/apple? 
// Left, Right, Middle?
enum class side { LEFT, RIGHT, MIDDLE, NONE };
side applePositions[NUM_APPLES];

int main()
{
	// Create a video mode object
	// Define your target resolution (e.g., 1920x1080)
	// This code should ensure that the game will full the screen regardless of resoultion
	Vector2i targetResolution(1920, 1080);

	// Create a window with the target resolution
	RenderWindow window(VideoMode(targetResolution.x, targetResolution.y), "Apple Dodge!!", sf::Style::Fullscreen);

	// Create a view with the target resolution
	View view(FloatRect(0, 0, targetResolution.x, targetResolution.y));
	window.setView(view);

	// Load the background image here and scale it to fit the target resolution
	Texture textureBackground;
	if (!textureBackground.loadFromFile("graphics/background.png"))
	{
		// Handle loading error
		return 1;
	}
	sf::Sprite spriteBackground(textureBackground);
	spriteBackground.setScale(static_cast<float>(targetResolution.x) / textureBackground.getSize().x, static_cast<float>(targetResolution.y) / textureBackground.getSize().y);
	//End of resolution code

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(-600, -2000);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Is the bee currently moving and direction
	bool beeActive = false;
	float beeDirection = rand() % 3 + 1;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureBird;

	// Load 1 new texture
	textureBird.loadFromFile("graphics/bird.png");

	// 3 New sprites withe the same texture
	Sprite spriteBird1;
	Sprite spriteBird2;
	Sprite spriteBird3;
	spriteBird1.setTexture(textureBird);
	spriteBird2.setTexture(textureBird);
	spriteBird3.setTexture(textureBird);

	// Position the clouds 
	spriteBird1.setPosition(0, 0);
	spriteBird2.setPosition(0, 150);
	spriteBird3.setPosition(0, 300);

	// Are the clouds currently on screen?
	bool Bird1Active = false;
	bool Bird2Active = false;
	bool Bird3Active = false;

	// How fast is each cloud?
	float Bird1Speed = 0.0f;
	float Bird2Speed = 0.0f;
	float Bird3Speed = 0.0f;

	// Initialize to -1 for leftward movement
	int BirdDirection = -1;

	// Variables to control time itself
	Clock clock;
	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;
	
	// The text on the screen
	Text messageText;
	Text scoreText;

	// We need to choose a font
	Font font;
	font.loadFromFile("fonts/Wooden Log.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setColor(Color::Red);
	scoreText.setColor(Color::Black);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Prepare the apples
	Texture textureApple;
	textureApple.loadFromFile("graphics/apple.png");

	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_APPLES; i++) {
		apple[i].setTexture(textureApple);
		apple[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		apple[i].setOrigin(220, 20);
	}

	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(200, 580);

	// The player starts on the left
	side playerSide = side::MIDDLE;

	// Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 2000);

	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	const float AXE_POSITION_MIDDLE = 887;

	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 2000);

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Control the player input
	bool acceptInput = false;

	// Prepare the sound
	// Dodging/Chopping Sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.mp3");
	Sound chop;
	chop.setBuffer(chopBuffer);

	// Death Sound
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.mp3");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	// Preparing Invinciblty
	bool invincible = false; 
	Clock invincibilityTimer; 
	// Duration of invincibility in seconds
	float invincibilityDuration = 5.0f; 
	// Text to display invincibility timer
	Text invincibilityText; 
	// Tracks whether the player has used invincibility
	bool invincibilityUsed = false; 

	// Preparing Invinciblty Text
	invincibilityText.setFont(font);
	invincibilityText.setCharacterSize(80);
	invincibilityText.setColor(Color::Black);
	invincibilityText.setPosition(20, 120); 

	// Preparing Dynamic Difficulty
	int playerDeaths = 0; // Initialize the player deaths count to 0
	float elapsedTime = 5.0f;

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F5)
				{
					// Capturing the window to a sf::Image
					Image screenshot = window.capture();


					// Making the screenshot name
					std::string screenshotName = "screenshot";

					// Saving to a file
					screenshot.saveToFile("screenshots/" + screenshotName + ".png");
				}
			}

			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}

		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Reset the elapsed time
			elapsedTime = 5.0f;

			// Reset Invinciblity
			invincibilityUsed = false;

			// Make all the apples disappear
			for (int i = 1; i < NUM_APPLES; i++)
			{
				applePositions[i] = side::NONE;
			}

			// Make sure the skull is hidden
			spriteRIP.setPosition(675, 2000);

			// Move the player into position
			spritePlayer.setPosition(650, 620);

			acceptInput = true;

		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(880, 620);

				// update the apples
				updateApples(score, elapsedTime, playerDeaths);

				// set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();

			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(320, 620);

				// update the apples
				updateApples(score, elapsedTime, playerDeaths);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();

			}
			// Handle the down cursor
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				// Make sure the player is on the left
				playerSide = side::MIDDLE;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_MIDDLE,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(620, 620);

				// update the apples
				updateApples(score, elapsedTime, playerDeaths);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();

			}
			// When the player uses invcinciblity
			if (Keyboard::isKeyPressed(Keyboard::I) && !invincibilityUsed)
			{
				invincible = true;
				invincibilityTimer.restart();
				invincibilityUsed = true; 
			}

		}
		if (invincible)
		{
			// Calculate remaining invincibility time
			float remainingInvincibilityTime = invincibilityDuration - invincibilityTimer.getElapsedTime().asSeconds();

			// Update the invincibility text
			std::stringstream invincibilityTextStream;
			invincibilityTextStream << "Invincibility: " << std::max(0.0f, remainingInvincibilityTime) << "s";
			invincibilityText.setString(invincibilityTextStream.str());

			// Check if invincibility has expired
			if (remainingInvincibilityTime <= 0.0f)
			{
				// Set Invinciblity to false
				invincible = false;

				// Hide the timer text
				invincibilityText.setString(""); 
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();
			elapsedTime += dt.asSeconds();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));


			if (timeRemaining <= 0.0f) 
			{

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play the out of time sound
				outOfTime.play();


			}


			// Setup the bee
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 300) + 400;

				// Set the initial position of the bee at the top-left corner of the screen
				spriteBee.setPosition(0, 0);
				beeActive = true;

				// Randomly determine the initial direction (1 for diagonal, 2 for left to right, 3 for right to left)
				int initialDirection = rand() % 3 + 1;
				float beeDirection = rand() % 3 + 1;
			}
			else
			{
				// Move the bee based on its direction
				float newX = spriteBee.getPosition().x;
				float newY = spriteBee.getPosition().y;

				if (beeDirection == 1) // Diagonal
				{
					newX += (beeSpeed * dt.asSeconds());
					newY += (beeSpeed * dt.asSeconds());
				}
				else if (beeDirection == 2) // Left to right
				{
					newX += (beeSpeed * dt.asSeconds());
				}
				else if (beeDirection == 3) // Right to left
				{
					newX -= (beeSpeed * dt.asSeconds());
				}

				spriteBee.setPosition(newX, newY);

				// Check if the bee has reached the screen boundaries
				if (newX > 1920 || newY > 1080 || newX < 0)
				{
					// Change direction randomly (1 for diagonal, 2 for left to right, 3 for right to left)
					int newDirection = rand() % 3 + 1;
					beeDirection = newDirection;

					// Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			// Manage the Birds
			// Birds 1-3 All Move left to right or right to left
			if (!Bird1Active)
			{
				// How fast is the Bird
				srand((int)time(0) * 30);
				Bird1Speed = (rand() % 1000) + 300;

				// Set the initial position of the Bird at the top-right or top-left corner of the screen
				int initialX = rand() % 2; // 0 for right, 1 for left
				int initialY = (rand() % 300) + 150;
				if (initialX == 0)
				{
					spriteBird1.setPosition(1920, initialY);
					BirdDirection = -1; // Move left
					spriteBird1.setScale(-1.f, 1.f);
				}
				else
				{
					spriteBird1.setPosition(0, initialY);
					BirdDirection = 1; // Move right
					spriteBird1.setScale(1.f, 1.f);
				}
				Bird1Active = true;
			}
			else
			{
				// Move Bird1 horizontally based on Bird Direction
				float newX = spriteBird1.getPosition().x + (Bird1Speed * BirdDirection * dt.asSeconds());
				spriteBird1.setPosition(newX, spriteBird1.getPosition().y);

				// Has the Bird1 reached the right or left edge of the screen?
				if ((BirdDirection == -1 && newX < -200) || (BirdDirection == 1 && newX > 1920))
				{
					// Set it up ready to change direction next frame
					Bird1Active = false;
				}
			}
			// Bird 2 
			if (!Bird2Active)
			{
				// How fast is the Bird
				srand((int)time(0) * 30);
				Bird2Speed = (rand() % 1500) + 330;

				// Set the initial position of the Bird at the top-right or top-left corner of the screen
				int initialX = rand() % 2; // 0 for right, 1 for left
				int initialY = (rand() % 500) + 50;
				if (initialX == 0)
				{
					spriteBird2.setPosition(1920, initialY);
					// Move left
					BirdDirection = -1; 
					spriteBird2.setScale(-1.f, 1.f);
				}
				else
				{
					spriteBird2.setPosition(0, initialY);
					// Move right
					BirdDirection = 1; 
					spriteBird2.setScale(1.f, 1.f);
				}
				Bird2Active = true;
			}
			else
			{
				// Move Bird2 horizontally based on Bird Direction
				float newX = spriteBird2.getPosition().x + (Bird2Speed * BirdDirection * dt.asSeconds());
				spriteBird2.setPosition(newX, spriteBird2.getPosition().y);

				// Has the bird reached the right or left edge of the screen?
				if ((BirdDirection == -1 && newX < -200) || (BirdDirection == 1 && newX > 1920))
				{
					// Set it up ready to change direction next frame
					Bird2Active = false;
				}
			}

			// Bird 3
			if (!Bird3Active)
			{
				// How fast is the bird
				srand((int)time(0) * 30);
				Bird3Speed = (rand() % 1000);

				// Set the initial position of the Bird at the top-right or top-left corner of the screen
				int initialX = rand() % 2; // 0 for right, 1 for left
				int initialY = (rand() % 150) + 150;
				if (initialX == 0)
				{
					spriteBird3.setPosition(1920, initialY);
					BirdDirection = -1; // Move left
					spriteBird3.setScale(-1.f, 1.f);
				}
				else
				{
					spriteBird3.setPosition(0, initialY);
					BirdDirection = 1; // Move right
					spriteBird3.setScale(1.f, 1.f);
				}
				Bird3Active = true;
			}
			else
			{
				// Move Bird3 horizontally based on cloud3Direction
				float newX = spriteBird3.getPosition().x + (Bird3Speed * BirdDirection * dt.asSeconds());
				spriteBird3.setPosition(newX, spriteBird3.getPosition().y);

				// Has the cloud reached the right or left edge of the screen?
				if ((BirdDirection == -1 && newX < -200) || (BirdDirection == 1 && newX > 1920))
				{
					// Set it up ready to change direction next frame
					Bird3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// update the apple sprites
			for (int i = 0; i < NUM_APPLES; i++)
			{

				float height = i * 150;

				if (applePositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					apple[i].setPosition(750, height);
					apple[i].setOrigin(220, 40);
					apple[i].setRotation(0);
				}
				else if (applePositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					apple[i].setPosition(1330, height);
					apple[i].setOrigin(220, 40);
					apple[i].setRotation(0);

				}
				else if (applePositions[i] == side::MIDDLE)
				{
					// Move the sprite to the Middle side
					apple[i].setPosition(1050, height);
					apple[i].setOrigin(220, 40);
					apple[i].setRotation(0);
				}
				else
				{
					// Hide the apple
					apple[i].setPosition(3000, height);
				}
			}

			// Handle a flying log				
			if (logActive)
			{

				spriteLog.setPosition(
				spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
				spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the insect reached the right hand edge of the screen?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new cloud next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// has the player been squished by a apple?
			if (applePositions[5] == playerSide && !invincible)
			{
				// death
				paused = true;
				acceptInput = false;
				
				// Dynamic Diffulity
				// If player score is over 100, the diffuility will rest back to normal
				if (score >= 100) 
				{
					playerDeaths = 0;
				}
				// If else, player deaths will increase and the diffulity will decearse when the player gets 3 deaths
				else
				{
					playerDeaths++;
				}
				
				// Draw the skull
				spriteRIP.setPosition(680, 560);

				// hide the player
				spritePlayer.setPosition(2000, 660);

				// Change the text of the message
				messageText.setString("DEATH!! HIT ENTER TO RESTART!");

				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);

				// Play the death sound
				death.play();

			}


		}
		// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		 // Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the Birds
		window.draw(spriteBird1);
		window.draw(spriteBird2);
		window.draw(spriteBird3);

		// Draw the flying log
		window.draw(spriteLog);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the Apples
		for (int i = 0; i < NUM_APPLES; i++) {
			window.draw(apple[i]);
		}

		// Draw the axe
		window.draw(spriteAxe);

		// Draw the player
		window.draw(spritePlayer);

		// Draw the gravestone
		window.draw(spriteRIP);

		// Draw the bee
		window.draw(spriteBee);

		// Draw the invincbility Timer
		if (invincible)
		{
			// Draw the invincibility timer text
			window.draw(invincibilityText);
		}
		// Draw the score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);


		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just drew
		window.display();

	}

	return 0;
}

// Function definition
void updateApples(int seed, float elapsedTime, int playerDeaths)
{

	// Calculate the branch spawn interval based on elapsed time
	float spawnInterval = 0.5f - (elapsedTime / 20.0f); // Adjust the division factor for desired difficulty curve

	// Ensure the spawn interval doesn't go below a minimum value
	if (spawnInterval < 0.1f)
	{
		spawnInterval = 0.1f;
	}

	// Check if the player has died 3 or more times with a score less than 50
	if (playerDeaths >= 3 && score < 50)
	{
		// Reduce the spawn interval to make the game easier
		spawnInterval += 1.0f; // 
	}

	if (elapsedTime > spawnInterval)
	{
		// Move all the branches down one place
		for (int j = NUM_APPLES - 1; j > 0; j--)
		{
			applePositions[j] = applePositions[j - 1];
		}

		// Spawn a new branch at position 0
		// LEFT, RIGHT or NONE
		srand((int)time(0) + seed);
		int r = (rand() % 5) + spawnInterval;

		switch (r)
		{
		case 0:
			applePositions[0] = side::LEFT;
			break;

		case 1:
			applePositions[0] = side::RIGHT;
			break;

		case 2: // Add a case for the middle position
			applePositions[0] = side::MIDDLE;
			break;

		default:
			applePositions[0] = side::NONE;
			break;
		}
		// Reset the elapsed time for the next branch spawn
		elapsedTime = 0.0f;

	}
}