#pragma once
#include "headersProject.h"
#include "Player.h"
#include "MapEditor.h"
#include "MapDrawer.h"

class UIGamePage;

class GamePage
{
private:
	Player player;

	UIGamePage* ui;

	MapEntity map[169];

	bool inGame = false;
	bool hasWin;

	bool CheckPlayerCanMove();

public: 
	GamePage();
	~GamePage();

	void LoadPage();
	void Update();
};

