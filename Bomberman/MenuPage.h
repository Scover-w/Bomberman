#pragma once
#include "headersProject.h"
#include "MapDrawer.h"

class UIMenuPage;

class MenuPage
{
	UIMenuPage* ui;

	Page wishPage;

	bool inAnimation = false;
	bool directionAnimation;
	float timerAnimation = 0.0f;

	void ManageEvent();
	void ManageMap();

public:
	MenuPage();
	~MenuPage();

	void PlayClick();
	void EditorClick();

	void LoadPage();
	void Update();
};

