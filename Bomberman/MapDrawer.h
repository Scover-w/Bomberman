#pragma once
#include "headersProject.h"
#include <stdlib.h> 
#include <time.h>   

class MapDrawer
{
private:
	IMageUI destructables[14];
	IMageUI walls[4];
	IMageUI grounds[16];

	IMageUI wallEnvImg;

	int selectedWall;
	int selectedDestructable;
	int selectedGround;

	MapEntity* map;
public:
	static MapDrawer* instance;
	MapDrawer();
	~MapDrawer();
	void SetMap(MapEntity(&map2)[169], bool isEditor);
	void DrawEnv(bool);
	void Draw();
};

