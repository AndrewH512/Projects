#include "Ball.h"

// This the constructor function
Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(50, 40));
	m_Shape.setPosition(m_Position);

	// Initialize horizontal velocity 
	m_DirectionX = 0.2f; 
}

// Applies Drag 
void Ball::applyDrag()
{
	m_DirectionX *= m_DragFactor;
	m_DirectionY *= m_DragFactor;
}

// Gets Position of Ball
sf::FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}

// Gets the Shape of Ball
sf::RectangleShape Ball::getShape()
{
	return m_Shape;
}

// Gets the X Value
float Ball::getXVelocity()
{
	return m_DirectionX;
}

// Gets the Y Value
float Ball::getYVelocity()
{
	return m_DirectionY;
}

// Increases the Speed of Ball
void Ball::increaseSpeed()
{
	m_Speed *= m_SpeedIncreaseFactor;

}
// Rests the Ball Speed when player dies
void Ball::resetSpeed()
{
	// Initialize horizontal velocity and speed
	m_Speed = 1000.0f; 
	m_DirectionX = 0.2f;
	m_DirectionY = 0.2f;

}
//  Set the speed for the ability 
void Ball::resetAbilitySpeed()
{
	// Initialize Speed
	m_Speed = 2000.0f;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX; 
}

void Ball::reboundBat()
{
	m_DirectionX = -m_DirectionX;

}

void Ball::reboundBottomorTop()
{
	m_DirectionY = -m_DirectionY; 
}

// Resets the Ball Back to Postion
void Ball::reset(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_DirectionX = -m_DirectionX; 
}

// Reduce the speed of the ball for ability
void Ball::reduceSpeed()
{
	m_Speed /= 2.0f; 
}
// Update Ball Position
void Ball::update(sf::Time dt)
{
	// Update the ball position variables
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the ball and the bat
	m_Shape.setPosition(m_Position);
}