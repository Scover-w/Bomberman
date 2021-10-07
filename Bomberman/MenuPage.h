#pragma once
#include "headersProject.h"

class MenuPage
{
	Texture shaderT;
	Sprite shaderS;

	Shader shader;
	Clock clk;
public:
	MenuPage();
	~MenuPage();

	void Update();
};

