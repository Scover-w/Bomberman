#include "BotPlayer.h"

BotPlayer::BotPlayer() : Player()
{

}

BotPlayer::~BotPlayer()
{

}

int BotPlayer::GetManhattanDistance(Vector2i v1, Vector2i v2)
{
	return (abs(v1.x - v2.x) + abs(v1.y - v2.y));
}

bool BotPlayer::IsCellValid(int x, int y)
{
	return (x > -1 && y > -1 && x < 13 && y < 13);
}