#pragma once
#include "headersProject.h"

class MapDrawer
{
private:
	int selectedWall;
	int selectedDBlock;

	Texture mapEntitiesT[2];
	Sprite mapEntitiesS[2];

	MapEntity* map;
public:
	static MapDrawer* instance;
	MapDrawer();
	~MapDrawer();
	void SetMap(MapEntity(&map2)[169]);
	void Draw();
};

