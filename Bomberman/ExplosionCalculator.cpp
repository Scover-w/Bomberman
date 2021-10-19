#include "ExplosionCalculator.h"
#include <iostream>
using namespace std;

ExplosionCalculator::ExplosionCalculator()
{

}

ExplosionCalculator::~ExplosionCalculator()
{

}

void ExplosionCalculator::SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapC)[169])
{
	map = map2;
	mapExplosion = mapE;
	mapCollectable = mapC;
}

ExplosionData ExplosionCalculator::GetData(int positionId, int range)
{
	Vector2i pos(positionId % Settings::NB_HEIGHT_MAP, positionId / Settings::NB_HEIGHT_MAP);

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

	MapEntity entity = *(map + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + ((position.y - 1) * Settings::NB_HEIGHT_MAP + position.x)) = 0.0f;

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(position.x, position.y - 1);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(position.x, position.y - 1);
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

	MapEntity entity = *(map + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + ((position.y + 1) * Settings::NB_HEIGHT_MAP + position.x)) = 0.0f;

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(position.x, position.y + 1);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(position.x, position.y + 1);
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

	MapEntity entity = *(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1)));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	
	*(mapExplosion + (position.y * Settings::NB_HEIGHT_MAP + (position.x - 1))) = 0.0f;

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(position.x - 1, position.y);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(position.x - 1, position.y);
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

	MapEntity entity = *(map + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1)));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	*(mapExplosion + (position.y * Settings::NB_HEIGHT_MAP + (position.x + 1))) = 0.0f;

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(position.x + 1, position.y);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(position.x + 1, position.y);
	}

	delta--;
	if (delta == 0)
		return 0;

	position.x++;
	return AskXRight(position, delta);
}

void ExplosionCalculator::PutCollectable(int x, int y)
{
	int i = (y * Settings::NB_HEIGHT_MAP + x);

	if (CustomRandom::GetRandom(0, 2))
	{
		*(map + i) = MapEntity::None;
		return;
	}

	switch (CustomRandom::GetRandom(0, 4))
	{
		case 0:
			*(map + i) = MapEntity::LifeIt;
			break;
		case 1:
			*(map + i) = MapEntity::BombIt;
			break;
		case 2:
			*(map + i) = MapEntity::SpeedIt;
			break;
		default:
			*(map + i) = MapEntity::PowerIt;
			break;
	}

	*(mapCollectable + i) = 0.0f;
}

void ExplosionCalculator::RemoveCollectable(int x, int y)
{
	int i = (y * Settings::NB_HEIGHT_MAP + x);
	*(map + i) = MapEntity::None;
	*(mapCollectable + i) = -1.0f;
}