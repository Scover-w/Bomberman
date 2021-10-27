#pragma once
#include "headersProject.h"
#include "Player.h"

class BotPlayer : Player
{
private:
	static MapEntity* map;
	int GetDistance(Vector2i, Vector2i);
	bool IsCellValid(int, int);

public:
	BotPlayer();
	~BotPlayer();

	static void SetMap(MapEntity*);
};

/*
A* :
heuristic -> Manhattan Distance

*/