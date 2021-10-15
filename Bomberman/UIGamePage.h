#pragma once
#include "GamePage.h"
class UIGamePage
{
private:
	GamePage* page;
public:
	UIGamePage(GamePage*);
	~UIGamePage();

	void Update();
	void Draw();

};

