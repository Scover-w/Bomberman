#pragma once
#include <corecrt_math_defines.h>
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <iostream>
using namespace std;
using namespace sf;


// UM : UI Map

class CustomMath
{
	static const float rotation;
public:
	// GM : GameMap
	static Vector2i GM_PositionToCoord(int);
	static int GM_CartCoordFToPosition(Vector2f);

	static Vector2f GM_PositionToCartCoordF(int);
	static Vector2f GM_PositionToIsoCoordF(int);

	
	static Vector2f GM_CartesianToIsometric(Vector2f cart);
	static Vector2f GM_IsometricToCartesian(Vector2f cart);

	// UM : UI Map
	static Vector2i UM_PositionToCoord(int);
	static int UM_CartCoordFToPosition(Vector2f);

	static Vector2f UM_PositionToCartCoordF(int);
	static Vector2f UM_PositionToIsoCoordF(int);


	static Vector2f UM_CartesianToIsometric(Vector2f cart);
	static Vector2f UM_IsometricToCartesian(Vector2f cart);
};

