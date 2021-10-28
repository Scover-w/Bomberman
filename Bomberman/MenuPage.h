#pragma once
#include "headersProject.h"
#include "MapDrawer.h"

class UIMenuPage;

class MenuPage
{
	UIMenuPage* ui;

	Texture shaderT;
	Sprite shaderS;

	Shader shader;
	Clock clk;

	Page wishPage;

	bool inAnimation = false;
	bool directionAnimation;
	float timerAnimation = 0.0f;

public:
	MenuPage();
	~MenuPage();

	void LoadPage();
	void Update();

	void ManageEvent();
	void ManageMap();

	void PlayClick();
	void EditorClick();
};

