#pragma once
#include "headersProject.h"
#include "Player.h"
#include <stack>
#include "DirectionBot.h"

class BotPlayer : public Player
{
private:
	DirectionBot modelDirection;
	Vector2i modelDirectionV2i;

	DirectionBot potentialDirections[4];

	bool risingMiddleCell = false;

	bool IsInMiddleCell();
	void SetInverseDirection();
	void SetRandomDirection();

	bool AskPutBomb();
	void RemoveBomb();

	DirectionBot CanMoveToCell(int);
	DirectionBot GetInverseDirection(DirectionBot);

	bool IsDestroyableOrPlayerAround(int);


public:
	BotPlayer();
	~BotPlayer();

	void Reset();
	int Update();
};