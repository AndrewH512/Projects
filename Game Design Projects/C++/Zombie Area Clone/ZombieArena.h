#pragma once
#include "Zombie.h"

using namespace sf;

// Creating the background class
int createBackground(VertexArray& rVA, IntRect arena);

// Creating the zombie horde class
Zombie* createHorde(int numZombies, IntRect arena);
