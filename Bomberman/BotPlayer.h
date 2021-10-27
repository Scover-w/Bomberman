#pragma once
#include "headersProject.h"
#include "Player.h"
#include "Cell.h"
#include <stack>

class BotPlayer : Player
{
private:
	static MapEntity* map;
	static int twodMap[13][13];
	int openMap[13][13];
	int closeMap[13][13];

	bool closedList[13][13];
	Cell cellDetails[13][13];

	stack<Vector2i> path;

	int GetDistance(const Vector2i&, const Vector2i&);
	bool IsValid(const Vector2i&);
	bool IsUnblocked(const Vector2i&);
	bool IsDestination(const Vector2i&, const Vector2i&);
	void SetPath(const Vector2i&);
	bool IsEqual(const Vector2i&, const Vector2i&);

public:
	BotPlayer();
	~BotPlayer();

	static void SetMap(MapEntity*);
	static void UpdateTwodMap();
	void SearchPath(const Vector2i&, const Vector2i&);
	void Coucou();
};