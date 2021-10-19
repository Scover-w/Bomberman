#pragma once
#include <SFML/Graphics.hpp>
#include "ExplosionData.h"
#include "MapEntity.h"
#include "Settings.h"
using namespace sf;

class ExplosionCalculator
{
private:
	MapEntity* map;
	float* mapExplosion;
public:
	ExplosionCalculator();
	~ExplosionCalculator();
	ExplosionData GetData(MapEntity(&map2)[169], float(&mapE)[169],int, int);
	int AskYUp(Vector2i, int);
	int AskYDown(Vector2i, int);
	int AskXLeft(Vector2i, int);
	int AskXRight(Vector2i, int);
};

