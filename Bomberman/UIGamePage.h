#pragma once
#include "GamePage.h"
class UIGamePage
{
private:
	GamePage* page;

	IMageUI blueGround;
	IMageUI redGround;
	IMageUI greenGround;
	IMageUI yellowGround;

	IMageUI heartUI;
	IMageUI bombUI;
	IMageUI lightUI;
	IMageUI powerUI;

	Vector2f groundUIBluePosition[8];
	Vector2f groundUIRedPosition[8];
	Vector2f groundUIGreenPosition[8];
	Vector2f groundUIYellowPosition[8];

	Vector2f itemPosition[32]; //first 16 is item p, rest is number p

	Text testText;

	void LoadImages();
	void LoadUIPositions();

public:
	UIGamePage(GamePage*);
	~UIGamePage();

	void Update();
	void Draw();
};

