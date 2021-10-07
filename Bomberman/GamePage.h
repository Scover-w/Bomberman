#pragma once
#include "headersProject.h"
#include "Player.h"

class GamePage
{
private:
	Player player;

public: 
	GamePage();
	~GamePage();

	void Update();
};

