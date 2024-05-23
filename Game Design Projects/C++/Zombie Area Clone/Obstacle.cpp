#include "Obstacle.h"
#include "TextureHolder.h"

using namespace sf;

obstacle::obstacle()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/obstacle.jpg"));
	float scaleFactor = 0.05f;
	m_Sprite.setScale(scaleFactor, scaleFactor);

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(0, 0);
}

FloatRect obstacle::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite obstacle::getSprite() const
{
	return m_Sprite;
}

// Spawning the obstacles
void obstacle::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize, std::vector<obstacle>& obstacles)
{
	// Can adjust this incase it spawns on the player
	const float minDistanceFromCenter = 120.0f; 

	do 
	{
		// Randomly generate obstacle position within the arena
		m_Position.x = static_cast<float>(std::rand() % arena.width);
		m_Position.y = static_cast<float>(std::rand() % arena.height);
	} 
	while (std::abs(m_Position.x - arena.width / 2.0f) < minDistanceFromCenter ||std::abs(m_Position.y - arena.height / 2.0f) < minDistanceFromCenter);

	// Set the position of the obstacle's sprite
	m_Sprite.setPosition(m_Position);

	// Store the obstacle in the vector of obstacles
	obstacles.push_back(*this);
}

// Checking for collisions
sf::FloatRect obstacle::getCollider() const
{
	return m_Sprite.getGlobalBounds();
}


bool obstacle::checkCollision(const sf::FloatRect& collider) const
{
	return m_Sprite.getGlobalBounds().intersects(collider);
}
