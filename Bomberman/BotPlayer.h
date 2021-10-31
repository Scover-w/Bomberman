#pragma once
#include "headersProject.h"
#include "Player.h"
#include "Cell.h"
#include <stack>
#include "DirectionBot.h"

class BotPlayer : public Player
{
private:
	DirectionBot modelDirection;
	Vector2i modelDirectionV;

	DirectionBot potentialDirections[4];

	bool risingMiddleCell = false;

	void SetInverseDirection();
	void SetRandomDirection();
	void RemoveBomb();
	bool IsInMiddleCell();
	DirectionBot CanMoveToCell(int);
	DirectionBot GetInverseDirection(DirectionBot);


public:
	BotPlayer();
	~BotPlayer();


	void Reset();
	int Update();
};