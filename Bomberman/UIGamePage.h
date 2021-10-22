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

	IMageUI shadow;

	Vector2f groundUIBluePosition[8];
	Vector2f groundUIRedPosition[8];
	Vector2f groundUIGreenPosition[8];
	Vector2f groundUIYellowPosition[8];

	Vector2f itemPosition[32]; //first 16 is item p, rest is number p

	Text testText;

	Color transparency;
	float time;
	Vector2f deltaItem;
	Vector2f deltaShadowNumber;

	void LoadImages();
	void LoadUIPositions();

	void SetTransparency(float);
	void SetDeltaItem(float);
	void DrawShadowItem(float, int);
	void DrawShadowNumber(float, int);

public:
	UIGamePage(GamePage*);
	~UIGamePage();

	void Update();
	void Draw();
};

