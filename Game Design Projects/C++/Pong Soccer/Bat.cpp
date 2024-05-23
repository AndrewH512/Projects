#include "Bat.h"

// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(100, 5));
	m_Shape.setPosition(m_Position);

	// Rotate the bat by 90 degrees to make it vertical
	m_Shape.setRotation(90);
	
	// Initialize vertical movement flags to false
	m_MovingUp = false;
	m_MovingDown = false;

	m_MovingRight = false;
	m_MovingLeft = false;

}

// Get Bat Position
sf::FloatRect Bat::getPosition()
{
	return m_Shape.getGlobalBounds();
}

// Get the bat Shape
sf::RectangleShape Bat::getShape()
{
	return m_Shape;
}
// Movement of the player
void Bat::stopUp()
{
	m_MovingUp = false;
}

void Bat::stopDown()
{
	m_MovingDown = false;
}

void Bat::stopLeft()
{
	// Stop leftward movement
	m_MovingLeft = false;
}

void Bat::stopRight()
{
	// Stop rightward movement
	m_MovingRight = false;
}

void Bat::moveUp()
{
	m_MovingUp = true;
}

void Bat::moveDown()
{
	m_MovingDown = true;
}

void Bat::moveLeft()
{
	m_MovingLeft = true;

}

void Bat::moveRight()
{
	m_MovingRight = true;
}

void Bat::update(sf::Time dt)
{
	// Prevent moving beyond the top of the screen
	if (m_MovingUp && m_Position.y > 0) 
	{
		m_Position.y -= m_Speed * dt.asSeconds(); 
	}
	// Prevent moving beyond the bottom of the screen
	if (m_MovingDown && m_Position.y + m_Shape.getSize().y < 1080) 
	{
		m_Position.y += m_Speed * dt.asSeconds(); 
	}
	// Moving Left, Prevent it from moving more than 20% across the screen
	if (m_MovingLeft && m_Position.x > 1500)
	{
		m_Position.x -= m_Speed * dt.asSeconds();
	}
	// Moving Right, Prevent it from going off screen
	if (m_MovingRight && m_Position.x < 1900)
	{
		m_Position.x += m_Speed * dt.asSeconds();
	}
	m_Shape.setPosition(m_Position);
}