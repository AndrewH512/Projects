#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::Vector2f m_Position;	
	sf::RectangleShape m_Shape;

	float m_Speed = 1000.0f;
	float m_SpeedIncreaseFactor = 1.8f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;
	float m_DragFactor = 0.99999f;

public:
	void applyDrag();

	Ball(float startX, float startY);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	void increaseSpeed();

	void resetSpeed();

	void resetAbilitySpeed();

	float getXVelocity();

	float getYVelocity();

	void reboundSides();

	void reboundBottomorTop();

	void reboundBat();

	void reduceSpeed();

	void reset(float x, float y);

	void update(sf::Time dt);

};
