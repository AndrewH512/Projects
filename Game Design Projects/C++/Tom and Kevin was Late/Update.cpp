#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "PlayableCharacter.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// These calls to spawn will be moved to a new
		// LoadLevel function soon
		// Spawn Thomas and Bob
		//m_Thomas.spawn(Vector2f(0,0), GRAVITY);
		//m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		// Make sure spawn is called only once
		//m_TimeRemaining = 10;
		//m_NewLevelRequired = false;

		// Load a level
		loadLevel();
		
	}

	if (m_Playing)
	{
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		{
			// Update George
			m_Thomas.update(dtAsSeconds);

			// Update Fido
			m_Kevin.update(dtAsSeconds);
		}
		else
		{
			// Update Thomas
			m_Thomas.update(dtAsSeconds);

			// Update Bob
			m_Bob.update(dtAsSeconds);
		}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			detectCollisions(m_Bob);
		}

		// Let bob and thomas jump on each others heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
		{
			m_Bob.stopFalling(m_Thomas.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
		{
			m_Thomas.stopFalling(m_Bob.getHead().top);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

		// Now Kevin and Thomas
		// Now doing the same thing but with Kevin and Thomas

		if (detectCollisions(m_Thomas) && detectCollisions(m_Kevin))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run kevins collision detection
			detectCollisions(m_Kevin);
		}

		// Let kevin and thomas jump on each others heads
		if (m_Kevin.getFeet().intersects(m_Thomas.getHead()))
		{
			m_Kevin.stopFalling(m_Thomas.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_Kevin.getHead()))
		{
			m_Thomas.stopFalling(m_Kevin.getHead().top);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Kevin run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
		
	// Set the appropriate view around the appropriate character
	if (m_SplitScreen)
	{
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		{
			m_LeftView.setCenter(m_Thomas.getCenter());
			m_RightView.setCenter(m_Kevin.getCenter());
		}
		else
		{
			m_LeftView.setCenter(m_Thomas.getCenter());
			m_RightView.setCenter(m_Bob.getCenter());
		}
	}
	else
	{
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		{
			if (m_Character1)
			{
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_Kevin.getCenter());
			}
		}
		else
		{
			// Centre full screen around appropriate character
			if (m_Character1)
			{
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_Bob.getCenter());
			}
		}
	}


	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.runningWater())
	{
		m_PS.update(dtAsSeconds, 0);
	}
	else if (m_PS.runningSand())
	{
		m_PS.update(dtAsSeconds, 1);
	}
	else if (m_PS.runningLava())
	{
		m_PS.update(dtAsSeconds, 2);
	}
	else if (m_PS.runningFinish())
	{
		m_PS.update(dtAsSeconds, 3);
	}
}// End of update function