#pragma once
#include "headersProject.h"

class UIStartPage;

class StartPage
{
private:
	UIStartPage* ui;

	Texture shaderT;
	Sprite shaderS;

	Shader shader;

	float animation = 0.0f;

	void ManageEvent();


public:
	StartPage();
	~StartPage();

	void LoadPage();
	void Update();
};

