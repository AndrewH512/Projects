#pragma once
#include <SFML/Audio.hpp>
#include "Observer.h"


using namespace sf;

class SoundManager : public Observer
{
private:
	// The buffers
	SoundBuffer m_FireBuffer;
	SoundBuffer m_FallInFireBuffer;
	SoundBuffer m_FallInWaterBuffer;
	SoundBuffer m_JumpBuffer;
	SoundBuffer m_ReachGoalBuffer;

	// The Sounds
	Sound m_Fire1Sound;
	Sound m_Fire2Sound;
	Sound m_Fire3Sound;
	Sound m_FallInFire;
	Sound m_FallInWater;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;

	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;

public:

	SoundManager();

	void playFire(Vector2f emitterLocation, Vector2f listenerLocation);
	void playJump();
	void playReachGoal();

	// Observer pattern methods
	void onPlayerFallInFire() override;
	void onPlayerFallInWater() override;
};

