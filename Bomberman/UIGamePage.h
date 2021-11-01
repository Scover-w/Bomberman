#pragma once
#include "GamePage.h"
class UIGamePage
{
private:
	GamePage* page;

	Player* player;

	BotPlayer* bot1;
	BotPlayer* bot2;
	BotPlayer* bot3;

	IMageUI blueGroundImg;
	IMageUI redGroundImg;
	IMageUI greenGroundImg;
	IMageUI yellowGroundImg;

	IMageUI heartUIImg;
	IMageUI bombUIImg;
	IMageUI lightUIImg;
	IMageUI powerUIImg;

	IMageUI shadowImg;

	Vector2f groundUIBluePositionV2f[8];
	Vector2f groundUIRedPositionV2f[8];
	Vector2f groundUIGreenPositionV2f[8];
	Vector2f groundUIYellowPositionV2f[8];

	Vector2f itemPosition[32]; //first 16 is item p, rest is number p

	Vector2f deltaItemV2f;
	Vector2f deltaShadowNumberV2f;
	Vector2f deltaTextV2f;

	Text valueItemsTxt;

	Color transparency;
	float time;
	

	void LoadImages();
	void LoadUIPositions();

	void SetTransparency(float);
	void SetDeltaItem(float);
	
	void SetLifePlayerText(int);
	void SetBombPlayerText(int);
	void SetRangePlayerText(int);
	void SetSpeedPlayerText(int);

	void DrawShadowItem(float, int);
	void DrawShadowNumber(float, int);

public:

	UIGamePage(GamePage*);
	~UIGamePage();

	void SetPlayers(Player*, BotPlayer*, BotPlayer*, BotPlayer*);
	
	void Update();
	void Draw();
};

