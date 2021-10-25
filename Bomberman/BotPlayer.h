#pragma once
#include "headersProject.h"
#include "Player.h"

class BotPlayer : Player
{
private:

	int GetManhattanDistance(Vector2i, Vector2i);
	bool IsCellValid(int, int);

public:
	BotPlayer();
	~BotPlayer();
};

/*
A* :
heuristic -> Manhattan Distance

*/