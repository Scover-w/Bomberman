#pragma once
#include "headersProject.h"

class UIStartPage;

class StartPage
{
private:

	Texture shaderT;
	Sprite shaderS;

	Shader shader;

	float animation = 0.0f;

	UIStartPage* ui;

public:
	StartPage();
	~StartPage();

	void LoadPage();
	void Update();
	void DrawText();
};

