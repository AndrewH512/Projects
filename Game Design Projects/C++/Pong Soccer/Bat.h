#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class Bat
{
private:
	sf::Vector2f m_Position;

	// A RectangleShape object
	sf::RectangleShape m_Shape;

	float m_Speed = 1000.0f;

	bool m_MovingUp = false;
	bool m_MovingDown = false;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;

public:
	Bat(float startX, float startY);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	void stopUp();

	void stopDown();

	void stopLeft(); 

	void stopRight(); 

	void update(sf::Time dt);

	void moveUp();

	void moveDown();

	void moveLeft(); 

	void moveRight(); 

};
