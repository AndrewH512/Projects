// Include headers and SFML files needed
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Bat.h"
#include "Ball.h"

using namespace sf;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Pong Soccer", Style::Fullscreen);

    // Create a texture to hold a graphic on the CPU
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(-50, 0);

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);

    // Prepare the Ball Sprite
    Texture textureBall;
    textureBall.loadFromFile("graphics/ball.png");
    Sprite spriteBall;
    spriteBall.setTexture(textureBall);

    // Set the score and lives
    int score = 0;
    int lives = 3;

    // Create a bat (initial position on the right side)
    Bat bat(1920 - 20, 1080 / 2);

    // Scale down the player sprite
    float scaleFactor = 0.023f; 
    spritePlayer.setScale(scaleFactor, scaleFactor);

    // Create a Ball with an initial position relative to the view
    Ball ball(window.getView().getSize().x / 2, window.getView().getSize().y / 2);

    // Set the Player Sprite to follow the bat
    spritePlayer.setPosition(bat.getPosition().left - 9, bat.getPosition().top);

    // Set the Ball Sprite to follow the ball
    spriteBall.setPosition(ball.getPosition().left - 9, ball.getPosition().top - 12);

    // Create a Text object called HUD
    Text hud;

    // Set the font
    Font font;
    font.loadFromFile("fonts/PlanetJoust.otf");
    hud.setFont(font);

    // Make the font big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20, 20);

    // Here is our clock for timing everything
    Clock clock;
    // Timer setup
    Clock timer;
    Time elapsedTime = Time::Zero;
    Time rewardInterval = seconds(45.0f);

    // Create Text for countdown timer
    Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(50);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(20, 1000);

    // Create a view
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // Flag to try prevent multiple scoring in one collision
    bool hasScored = false; 

    // Preparing the Sounds
    // When the ball hits a wall or player
    SoundBuffer kickBuffer;
    kickBuffer.loadFromFile("sounds/kick.mp3");
    Sound kick;
    kick.setBuffer(kickBuffer);

    // Losting a Life Sound
    SoundBuffer lostLifebuffer;
    lostLifebuffer.loadFromFile("sounds/lost life.mp3");
    Sound lostLife;
    lostLife.setBuffer(lostLifebuffer);

    // Gaining a Life Sound
    SoundBuffer gainLifebuffer;
    gainLifebuffer.loadFromFile("sounds/level up.mp3");
    Sound gainLife;
    gainLife.setBuffer(gainLifebuffer);

    // Special Ability Setup
    bool isSpecialAbilityActive = false;  
    Clock specialAbilityTimer;        
    Time specialAbilityDuration = sf::seconds(5.0f);  
    bool abilityUsed = false;

    // Create Text for special ability timer
    Text specialAbilityTimerText;
    specialAbilityTimerText.setFont(font);
    specialAbilityTimerText.setCharacterSize(50);  
    specialAbilityTimerText.setFillColor(sf::Color::White);
    specialAbilityTimerText.setPosition(1000, 1000);  

    while (window.isOpen())
    {
        /*
        Handle the player input
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            bat.moveUp();
        }
        else
        {
            bat.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            bat.moveDown();
        }
        else
        {
            bat.stopDown();
        }

        // NEW: the bat can now move left and right
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }
        // Ability: User Presses S to enable the special ablity
        if (Keyboard::isKeyPressed(Keyboard::S) && !abilityUsed)
        {
            // Set Ability Activte to true, and mark that the player used their ability
            isSpecialAbilityActive = true;
            specialAbilityTimer.restart();
            abilityUsed = true;

            // Checks to see if Ability is active
            if (isSpecialAbilityActive)
            {
                // Reduces the speed of ball
                ball.reduceSpeed();  
            }
        }

        /*
        Update the bat, the ball, and the HUD
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */
        // Update the delta time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        // Update the Timer
        elapsedTime += timer.restart();

        // Update the remaining time until next life
        Time remainingTime = rewardInterval - elapsedTime;

        // Check if the player has stayed alive for 45 seconds
        if (elapsedTime >= rewardInterval)
        {
            lives++;

            // Reset the timer
            elapsedTime = Time::Zero;

            gainLife.play();
        }

        // Apply drag to the ball
        ball.applyDrag();

        // Check if the ball has stopped 
        if (std::abs(ball.getXVelocity()) < 0.02f || std::abs(ball.getYVelocity()) < 0.02f)
        {
            // Remove a life
            lives--;

            // Play the lost life sound
            lostLife.play();

            // Reset the ball's position and speed
            ball.reset(window.getView().getSize().x / 2, window.getView().getSize().y / 2);
            ball.resetSpeed();
        }

        // Check if Ability is Active
        if (isSpecialAbilityActive)
        {
            // Check if the special ability duration has elapsed
            if (specialAbilityTimer.getElapsedTime() >= specialAbilityDuration)
            {
                // Deactivate the special ability and reset the timer
                isSpecialAbilityActive = false;
                specialAbilityTimer.restart();

                // Optionally, you can revert the ball's speed here
                if (!isSpecialAbilityActive)
                {
                    ball.resetAbilitySpeed(); 
                }
            }
        }
        if (isSpecialAbilityActive)
        {
            Time remainingSpecialAbilityTime = specialAbilityDuration - specialAbilityTimer.getElapsedTime();
            specialAbilityTimerText.setString("Slowdown Ability: " + std::to_string(static_cast<int>(remainingSpecialAbilityTime.asSeconds())) + "s");
        }
        else
        {
            specialAbilityTimerText.setString("");
        }

        // Update the sprites
        spritePlayer.setPosition(bat.getPosition().left, bat.getPosition().top);
        spriteBall.setPosition(ball.getPosition().left - 10, ball.getPosition().top - 12);

        // Update the HUD text
        std::stringstream ss;
        ss << "Score: " << score << "    Lives: " << lives;
        hud.setString(ss.str());

        // Timer Text
        countdownText.setString(" Next Life In: " + std::to_string(static_cast<int>(remainingTime.asSeconds())) + "s");

        // Reset the scoring flag
        hasScored = false;

        // Handle ball going off the right side of the screen
        if (ball.getPosition().left > window.getView().getSize().x)
        {
            // Reset the ball's position 
            ball.reset(window.getView().getSize().x / 2, window.getView().getSize().y / 2);

            // Reset Ball Speed
            ball.resetSpeed();

            // Remove a life
            lives--;

            // Play Sound
            lostLife.play();

            // Check for zero lives
            if (lives < 1) {
                // Reset the score
                score = 0;
                // Reset the lives
                lives = 3;

                // Reset ability
                abilityUsed = false;

                // Reset ability timer
                elapsedTime = Time::Zero;
                specialAbilityTimer.restart();

                // Reset Ball Speed
                ball.resetSpeed();
            }
        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBottomorTop();

            // Play Kick Sound
            kick.play();

        }

        // Handle ball hitting the bottom
        if (ball.getPosition().top + ball.getShape().getSize().y > window.getView().getSize().y)
        {
            ball.reboundBottomorTop();

            // Play kick sound
            kick.play();

        }

        // Handle ball hitting the left side
        if (ball.getPosition().left < 0)
        {
            
            ball.reboundSides();

            // Play kick sound
            kick.play();

            // Add a point to the player's score if not scored in this frame
            if (!hasScored) 
            {
                score++;
                hasScored = true;
            }
        }


        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // Hit detected, so reverse the ball and score a point if not scored in this frame
            ball.reboundBat();

            // Increase the ball's speed
            ball.increaseSpeed();

            // Play kick sound
            kick.play();

        }

        /*
        Draw the bat, the ball, timers, sprites and the HUD
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */
        window.clear();
        window.draw(spriteBackground);
       
        window.draw(hud);
        window.draw(countdownText);
        window.draw(specialAbilityTimerText);
        window.draw(bat.getShape());
        window.draw(ball.getShape());

        window.draw(spritePlayer);
        window.draw(spriteBall);

        window.display();
    }
    return 0;
}