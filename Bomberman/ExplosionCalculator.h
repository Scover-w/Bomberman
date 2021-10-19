#pragma once
#include <SFML/Graphics.hpp>
#include "ExplosionData.h"
#include "MapEntity.h"
#include "Settings.h"
#include "CustomRandom.h"
using namespace sf;

class ExplosionCalculator
{
private:
	MapEntity* map;
	float* mapExplosion;
	float* mapCollectable;
public:
	ExplosionCalculator();
	~ExplosionCalculator();
	void SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapC)[169]);
	ExplosionData GetData(int, int);
	int AskYUp(Vector2i, int);
	int AskYDown(Vector2i, int);
	int AskXLeft(Vector2i, int);
	int AskXRight(Vector2i, int);

	void PutCollectable(int, int);
	void RemoveCollectable(int, int);
};

