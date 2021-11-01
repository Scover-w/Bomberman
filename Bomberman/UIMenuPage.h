#pragma once
#include "MenuPage.h"
#include "PhysicalButton.h"
#include "MouseTool.h"

class UIMenuPage
{
private:
	MenuPage* page;

	PhysicalButton playPBtn;
	PhysicalButton editorPBtn;

public:
	UIMenuPage(MenuPage*);
	~UIMenuPage();

	void DisplayButtons();
	void HideButtons();
	
	void Update();
	void Draw();
};

