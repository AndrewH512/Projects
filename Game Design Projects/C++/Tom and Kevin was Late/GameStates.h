#pragma once
class LevelManager;  // Forward declaration

class GameStates
{
public:
    virtual ~GameStates() {}
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleInput(LevelManager& levelManager) = 0;
    virtual void update(LevelManager& levelManager, float elapsedTime) = 0;
};