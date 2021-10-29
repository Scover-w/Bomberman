#pragma once
#include "PhysicalButton.h"
#include "EndPage.h"
class UIEndPage
{
private:
	IMageUI groundImg;

	IMageUI winImg;
	IMageUI loseImg;
	PhysicalButton menuBtn;
	PhysicalButton restartBtn;

	EndPage* page;

	Color multiColor;

public:
	UIEndPage(EndPage*);
	~UIEndPage();

	void SetWin(bool);

	void DrawBackText();

	void Update();
	void Draw();
};

