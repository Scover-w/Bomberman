#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Timer
{
private:
	Clock clock;

	float deltaTime = 0.f;
	float speed = 120.0f;

public:
	static Timer* instance;
	Timer();
	~Timer();
	void SetDeltaTime();
	float GetDeltaTime();
};

