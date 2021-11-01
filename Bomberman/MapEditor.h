#pragma once
#include "headersProject.h"
#include <fstream>

class MapEditor
{
	static int unPlacableIndex[12];
public:
	static int GetMaxId();
	
	static void WriteMap(int, MapEntity(&map2)[169]);
	static bool DoesMapExist(int);
	
	static bool LoadMap(int, MapEntity(&map2)[169]);
	static void LoadRandomMap(MapEntity(&map2)[169]);
};

