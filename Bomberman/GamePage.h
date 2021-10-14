#pragma once
#include "headersProject.h"
#include "Player.h"

class UIGamePage;

class GamePage
{
private:
	Player player;

	UIGamePage* ui;

	bool inGame = false;
	bool hasWin;

public: 
	GamePage();
	~GamePage();

	void LoadPage();
	void Update();
};

