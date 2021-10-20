#pragma once
#include "headersProject.h"
#include "Player.h"
#include "MapEditor.h"
#include "MapDrawer.h"
#include "ExplosionCalculator.h"


class UIGamePage;

class GamePage
{
private:
	Player player;

	UIGamePage* ui;

	ExplosionCalculator explosionCalcul;

	MapEntity map[169];
	float mapExplosion[169];
	float mapBomb[169];
	int bombOwner[169];

	float animCollectable = 0.0f;

	bool inGame = false;
	bool hasWin;

	bool beforeSpace = false;
	bool currentSpace = false;

	void UpdateBombs(float);
	void UpdateExplosions(float);

public: 
	GamePage();
	~GamePage();

	void LoadPage();
	void Update();
};

