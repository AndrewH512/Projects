#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"

using namespace sf;
using namespace std;

class ParticleSystem : public Drawable
{
private:
	vector<Particle> m_Particles;
	VertexArray m_Vertices;
	float m_Duration;
	bool m_IsRunningWater = false;
	bool m_IsRunningLava = false;
	bool m_IsRunningSand = false;
	bool m_IsRunningFinish = false;


public:

	virtual void draw(RenderTarget& target, RenderStates states) const;

	void init(int count);

	void emitWaterParticles(Vector2f position);
	void emitSandParitcles(Vector2f position);
	void emitLavaParitcles(Vector2f position);
	void emitFinishParitcles(Vector2f position);

	void update(float elapsed, int Particle_number);

	bool runningWater();
	bool runningLava();
	bool runningSand();
	bool runningFinish();


};


