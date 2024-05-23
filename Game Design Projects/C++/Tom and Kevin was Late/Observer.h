#pragma once
class Observer
{
public:
    virtual ~Observer() {}
    virtual void onPlayerFallInFire() = 0;
    virtual void onPlayerFallInWater() = 0;
};