#pragma once
#include "headersProject.h"
#include "Player.h"
#include "MapEditor.h"
#include "MapDrawer.h"
#include "ExplosionCalculator.h"
#include "BotPlayer.h"


class UIGamePage;

class GamePage
{
private:
	UIGamePage* ui;

	Player player;

	BotPlayer bot1;
	BotPlayer bot2;
	BotPlayer bot3;

	ExplosionCalculator explosionCalcul;

	MapEntity map[169];

	float mapExplosion[169];
	float mapBomb[169];

	int bombOwner[169];

	bool inGame = false;
	bool hasWin;

	bool beforeSpace = false;
	bool currentSpace = false;

	bool tempTest = false;

	void UpdateBombs(float);
	void UpdateExplosions(float);
	void PoseBomb(int, int);

public: 
	GamePage();
	~GamePage();

	void ManageEvent();
	void CheckEndGame();

	void LoadPage();
	void Update();
	
	
};

