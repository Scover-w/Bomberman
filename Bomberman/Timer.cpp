#include "Timer.h"

Timer* Timer::instance;

Timer::Timer()
{
    instance = this;
    clock.restart();
}
Timer::~Timer()
{

}

void Timer::SetDeltaTime()
{
    deltaTime = clock.getElapsedTime().asSeconds();

    timeSpent += deltaTime;
    clock.restart();
}

float Timer::GetDeltaTime()
{
    return deltaTime;
}

float Timer::GetTimeSpent()
{
    return timeSpent;
}
