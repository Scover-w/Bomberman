#pragma once
#include <corecrt_math_defines.h>
#include <SFML/Graphics.hpp>
#include "Settings.h"
using namespace sf;

class CustomMath
{
	static const float rotation;
public:
	static Vector2i PositionToCoord(int);
	static int CoordToPosition(sf::Vector2i);

	static Vector2f PositionToCartCoordF(int);
	static Vector2f PositionToIsoCoordF(int);

	
	static Vector2f CartesianToIsometric(Vector2f cart);
	static Vector2f IsometricToCartesian(Vector2f cart);


	// Draw env function
	static Vector2f EnvCartesianToIsometric(Vector2f cart);
	static Vector2f EnvIsometricToCartesian(Vector2f cart);

	static Vector2f EnvPositionToIsoCoordF(int);
};

