#pragma once
#include "headersProject.h"
#include "Player.h"
#include "Cell.h"
#include <stack>

class BotPlayer : public Player
{
private:
	Vector2f modelDirection;

	void SetRandomDirection();
	void RemoveBomb();

public:
	BotPlayer();
	~BotPlayer();

	void Reset();
	int Update();
};