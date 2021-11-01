#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Timer
{
private:
	Clock clock;

	float timeSpent = 0.0f;
	float deltaTime = 0.f;

public:
	static Timer* instance;

	Timer();
	~Timer();

	void SetDeltaTime();
	float GetDeltaTime();
	float GetTimeSpent();
};

