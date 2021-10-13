#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StaticWindow.h"
#include "CursorManager.h"
using namespace sf;
using namespace std;

class IMageUI
{
protected:
	Sprite sprite;
	Texture texture;

public:
	IMageUI();
	~IMageUI();
	void SetTexture(string);
	void Draw();
	void SetOrigin(float, float);
	void SetPosition(float, float);
	void SetScale(float, float);
	void SetOrigin(Vector2f);
	void SetPosition(Vector2f);
	void SetScale(Vector2f);
	void SetRotation(float);
	void SetColor(Color&);
	void SetTextureRect(IntRect&);
};

