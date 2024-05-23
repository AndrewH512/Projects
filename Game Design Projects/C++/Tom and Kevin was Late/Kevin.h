#include "PlayableCharacter.h"


class Kevin : public PlayableCharacter
{
public:
	// A constructor specific to Kevin
	Kevin();

	// The overriden input handler for Kevin
	bool virtual handleInput();

};