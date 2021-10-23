#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Settings
{
public:
	static const Vector2i SIZE_SCREEN;
	
	static const float ZOOM;

	static const Vector2f MULTIPLIED_SIZE_SCREEN;

	static const int SIZE_GAME_MAP;
	static const int SIZE_UI_MAP;

	static const float ISOMETRIC_SIZE_TILE;

	static const float CARTESIAN_ATOMIC_HEIGHT;

	static const Vector2f GAME_TRANSLATION_MAP;
	static const Vector2f UI_TRANSLATION_MAP;

	// 80, 39
};

/*
https://stackoverflow.com/questions/1469149/calculating-vertices-of-a-rotated-rectangle

https://opengameart.org/content/mega-isometric-block-pack
*/