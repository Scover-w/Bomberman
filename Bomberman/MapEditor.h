#pragma once
#include "headersProject.h"
#include <fstream>

class MapEditor
{
public:

	static bool LoadMap(int, MapEntity(&map2)[169]);
	static void WriteMap(int, MapEntity(&map2)[169]);
	static bool DoesMapExist(int);
	static int GetMaxId();
};

