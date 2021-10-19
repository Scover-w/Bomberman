#pragma once
#include <SFML/Graphics.hpp>
typedef struct ExplosionData ExplosionData;

struct ExplosionData
{
public:
	int xRight;
	int xLeft;
	int yUp;
	int yDown;
	sf::Vector2i centerId;
};