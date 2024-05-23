#include "zombie.h"
#include "TextureHolder.h"
#include "Obstacle.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	// Set the type of the zombie
	m_Type = type; 

	// Initialize the hit count
	m_HitCount = 0;    

	// Initialize the fleeing state and set the initial fleeing time (in seconds)
	m_Fleeing = false;   
	m_FleeTime = 1.0f;  

	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = 40;
		m_Health = 5;

		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = 70;
		m_Health = 2;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = 20;
		m_Health = 3;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}
	// Bloater
	if (m_Type == 0) 
	{
		// Stop the Bloater for 1 second and then increase speed
		m_Fleeing = true;
		m_FleeTime = 1.0f;
		m_Speed = 0; // Stop the Bloater
	}
	// Chaser
	if (m_Type == 1)
	{
		// Increase hit count
		m_HitCount++; 

		// Set Fleeing to True
		m_Fleeing = true;

		// Set Fleeing time to 1 second
		m_FleeTime = 1.0f; 
	}

	// Crawler 
	if (m_Type == 2) 
	{
		// Crawler is hit but not dead yet
		// Increase its speed
		m_Speed *= 2; 
	}

	return false;
}

// Is the zombie alive?
bool Zombie::isAlive()
{
	return m_Alive;
}

// Get zombie position
FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

// Get the sprite
Sprite Zombie::getSprite()
{
	return m_Sprite;
}

// Update the zombies
void Zombie::update(float elapsedTime, Vector2f playerLocation, const std::vector<obstacle>& obstacles)
{
	// Player location
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	Vector2f newPosition = m_Position;


	// Crawlers will flee from the player when hit for 1 second and then resume the chase.
	// Bloaters will be stunned for 1 second, stop and then resume the chase
	if (m_Fleeing)
	{
		// Reduce the fleeing time
		m_FleeTime -= elapsedTime;

		if (m_FleeTime <= 0)
		{
			// Stunned time is up resume chasing
			// Bloater
			m_Fleeing = false;
			if (m_Type == 0) 
			{
				// is no longer stunned, increase speed
				m_Speed = BLOATER_SPEED + 0.5f; 
			}
		}
		else
		{
			// Flee from the player
			float playerX = playerLocation.x;
			float playerY = playerLocation.y;

			// Update the zombie position variables to move away from the player
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x - m_Speed * elapsedTime;
			}

			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y - m_Speed * elapsedTime;
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x + m_Speed * elapsedTime;
			}

			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y + m_Speed * elapsedTime;
			}

		}
	}
	else
	{

		// Update the zombie position variables
		if (playerX > m_Position.x)
		{
			m_Position.x = m_Position.x +
				m_Speed * elapsedTime;
		}

		if (playerY > m_Position.y)
		{
			m_Position.y = m_Position.y +
				m_Speed * elapsedTime;
		}

		if (playerX < m_Position.x)
		{
			m_Position.x = m_Position.x -
				m_Speed * elapsedTime;
		}

		if (playerY < m_Position.y)
		{
			m_Position.y = m_Position.y -
				m_Speed * elapsedTime;
		}

	}

	// Collision code for zombies
	// This code is make sure the zombies do not get stuck and also can't walk through the walls
	// Iterate through obstacles and check for collisions
	for (const obstacle& obs : obstacles) 
	{
		// Get the collision bounds for the zombie and the obstacle
		FloatRect zombieBounds = m_Sprite.getGlobalBounds();
		FloatRect obstacleBounds = obs.getCollider();

		// Check for collision
		if (zombieBounds.intersects(obstacleBounds)) 
		{
			// Calculate the intersection between zombie and obstacle bounds
			FloatRect intersection;
			if (zombieBounds.intersects(obstacleBounds, intersection)) 
			{
				// Determine the direction of the collision
				float dx = zombieBounds.left + zombieBounds.width / 2 - obstacleBounds.left - obstacleBounds.width / 2;
				float dy = zombieBounds.top + zombieBounds.height / 2 - obstacleBounds.top - obstacleBounds.height / 2;

				// Adjust zombie's position to move away from the obstacle
				if (std::abs(dx) > std::abs(dy)) 
				{
					// Collided horizontally, move away vertically
					if (dx > 0) 
					{
						m_Position.x += intersection.width;
					}
					else 
					{
						m_Position.x -= intersection.width;
					}
				}
				else 
				{
					// Collided vertically, move away horizontally
					if (dy > 0) 
					{
						m_Position.y += intersection.height;
					}
					else 
					{
						m_Position.y -= intersection.height;
					}
				}

				// Update the zombie's sprite position
				m_Sprite.setPosition(m_Position);
			}
		}
	}

	m_Sprite.setPosition(m_Position);


	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;

	m_Sprite.setRotation(angle);
}