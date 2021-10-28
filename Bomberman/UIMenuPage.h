#pragma once
#include "MenuPage.h"
#include "PhysicalButton.h"
#include "MouseTool.h"

class UIMenuPage
{
private:
	MenuPage* page;

	PhysicalButton playBtn;
	PhysicalButton editorBtn;

public:
	UIMenuPage(MenuPage*);
	~UIMenuPage();

	void Update();
	void Draw();

	void DisplayButtons();
	void HideButtons();
};

