#pragma once
#include "PhysicalButton.h"
#include "EndPage.h"
class UIEndPage
{
private:
	EndPage* page;

	IMageUI groundImg;
	IMageUI winImg;
	IMageUI loseImg;

	PhysicalButton menuPBtn;
	PhysicalButton restartPBtn;

	Color multiColor;

public:

	UIEndPage(EndPage*);
	~UIEndPage();

	void SetWin(bool);
	void DrawBackText();

	void Update();
	void Draw();
};

