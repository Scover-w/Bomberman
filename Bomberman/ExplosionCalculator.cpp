#include "ExplosionCalculator.h"
#include <iostream>
using namespace std;

ExplosionCalculator::ExplosionCalculator()
{

}

ExplosionCalculator::~ExplosionCalculator()
{

}

ExplosionData ExplosionCalculator::GetData(MapEntity(&map2)[169], float(&mapE)[169], int positionId, int range)
{

	Vector2i pos(positionId % Settings::NB_HEIGHT_MAP, positionId / Settings::NB_HEIGHT_MAP);

	map = map2;
	mapExplosion = mapE;

	ExplosionData entity;

	entity.centerId = pos;
	entity.xRight = range - AskXRight(pos, range);
	entity.xLeft = range - AskXLeft(pos, range);
	entity.yUp = range - AskYUp(pos, range);
	entity.yDown = range - AskYDown(pos, range);

	*(mapExplosion + (pos.y * Settings::NB_HEIGHT_MAP + pos.x)) = 0.0f;

	return entity;
}

int ExplosionCalculator::AskYUp(Vector2i position, int delta)
{
	if (position.y - 1 < 0)
		return delta;

	if ( *(map + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x)) == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x)) = 0.0f;

	if (*(map + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x)) == MapEntity::DBlock)
	{
		*(map + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x)) = MapEntity::None;
		return delta - 1;
	}

	delta--;
	if (delta == 0)
		return 0;

	position.y--;
	return AskYUp(position, delta);
}

int ExplosionCalculator::AskYDown(Vector2i position, int delta)
{
	if (position.y + 1 > 12)
		return delta;

	if (*(map + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x)) == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x)) = 0.0f;

	if (*(map + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x)) == MapEntity::DBlock)
	{
		*(map + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x)) = MapEntity::None;
		return delta - 1;
	}
	delta--;
	if (delta == 0)
		return 0;

	position.y++;
	return AskYDown(position, delta);
}

int ExplosionCalculator::AskXLeft(Vector2i position, int delta)
{
	if (position.x - 1 < 0)
		return delta;

	if (*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1))) == MapEntity::Wall)
	{
		return delta;
	}

	
	*(mapExplosion + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1))) = 0.0f;

	if (*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1))) == MapEntity::DBlock)
	{
		*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1))) = MapEntity::None;
		return delta - 1;
	}
	delta--;
	if (delta == 0)
		return 0;

	position.x--;
	return AskXLeft(position, delta);
}

int ExplosionCalculator::AskXRight(Vector2i position, int delta)
{
	if (position.x + 1 > 12)
		return delta;

	if (*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1))) == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1))) = 0.0f;

	if (*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1))) == MapEntity::DBlock)
	{
		*(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1))) = MapEntity::None;
		return delta - 1;
	}

	delta--;
	if (delta == 0)
		return 0;

	position.x++;
	return AskXRight(position, delta);
}