#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

using namespace sf;

class Zombie
{
private:
	// How fast is each zombie type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	// How tough is each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 2;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;
	
	// What type of zombie?
	int m_Type;

	int m_HitCount;
	bool m_Fleeing;  
	float m_FleeTime;


	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Which zombie type is it?
	int getType() { return m_Type; }

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation, const std::vector<obstacle>& obstacles);

};


