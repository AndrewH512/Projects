#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class obstacle
{
public:

	// Create obstacle
	obstacle();

	// Where is the obstacle
	sf::FloatRect getPosition();

	// Send a copy of the sprite to main
	sf::Sprite getSprite() const;

	// Parameter to the spawn method to store the obstacles
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize, std::vector<obstacle>& obstacles);

	// Retrieve the obstacle's collider
	sf::FloatRect getCollider() const;

	// Check for collisions with players and zombies
	bool checkCollision(const sf::FloatRect& collider) const;


private:
	// Where is the obstacle
	sf::Vector2f m_Position;

	// Sprite for the obstacle
	sf::Sprite m_Sprite;

	// And a texture
	sf::Texture m_Texture;

	// What is the screen resolution
	sf::Vector2f m_Resolution;

	// What size is the current arena
	sf::IntRect m_Arena;

	// How big is each tile of the arena
	int m_TileSize;

};