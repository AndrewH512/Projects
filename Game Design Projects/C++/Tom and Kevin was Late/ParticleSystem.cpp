#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles)
{
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(numParticles);

	// Create the particles

	for (int i = 0; i < numParticles; i++)
	{
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;
		float radius = (rand() % 600) + 1000.f;


		Vector2f direction;

		direction = Vector2f(cos(angle) * speed,
			sin(angle) * speed);

		m_Particles.push_back(Particle(direction, radius));

	}

}

void ParticleSystem::update(float dt, int Particle_number)
{
	m_Duration -= dt;
	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		// Move the particle
		(*i).update(dt);

		// Update the vertex array
		m_Vertices[currentVertex].position = (*i).getPosition();

		// Move to the next vertex
		currentVertex++;
	}

	if (m_Duration < 0)
	{
		m_IsRunningWater = false;
		m_IsRunningSand = false;
	}

}

// Water Particles
void ParticleSystem::emitWaterParticles(Vector2f startPosition)
{
	m_IsRunningWater = true;
	m_Duration = 1;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Blue;
		(*i).setPosition(startPosition);

		currentVertex++;
	}

}

// Sand Particles
void ParticleSystem::emitSandParitcles(Vector2f startPosition)
{
	m_IsRunningSand = true;
	m_Duration = 5;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Yellow;
		(*i).setPosition(startPosition);

		currentVertex++;
	}

}

// Lava Particles
void ParticleSystem::emitLavaParitcles(Vector2f startPosition)
{
	m_IsRunningLava = true;
	m_Duration = 1;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Red;
		(*i).setPosition(startPosition);

		currentVertex++;
	}

}

// Finish Paritcles
void ParticleSystem::emitFinishParitcles(Vector2f startPosition)
{
	m_IsRunningFinish = true;
	m_Duration = 2;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Green;
		(*i).setPosition(startPosition);

		currentVertex++;
	}

}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	
	target.draw(m_Vertices, states);
}

bool ParticleSystem::runningWater()
{
	return m_IsRunningWater;
}

bool ParticleSystem::runningSand()
{
	return m_IsRunningSand;
}

bool ParticleSystem::runningLava()
{
	return m_IsRunningLava;
}

bool ParticleSystem::runningFinish()
{
	return m_IsRunningFinish;
}