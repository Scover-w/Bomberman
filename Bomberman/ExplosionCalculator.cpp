#include "ExplosionCalculator.h"
#include <iostream>
using namespace std;

ExplosionCalculator::ExplosionCalculator()
{

}
ExplosionCalculator::~ExplosionCalculator()
{

}


#pragma region Private
int ExplosionCalculator::AskYUp(Vector2i position, int delta)
{
	if (position.y - 1 < 0)
		return delta;

	MapEntity entity = *(map + ((position.y - 1) * Settings::SIZE_GAME_MAP + position.x));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	int i = ((position.y - 1) * Settings::SIZE_GAME_MAP + position.x);

	UpdatePosition(i);

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(i);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(i);
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

	MapEntity entity = *(map + ((position.y + 1) * Settings::SIZE_GAME_MAP + position.x));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	int i = ((position.y + 1) * Settings::SIZE_GAME_MAP + position.x);
	UpdatePosition(i);

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(i);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(i);
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

	MapEntity entity = *(map + (position.y * Settings::SIZE_GAME_MAP + (position.x - 1)));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	int i = (position.y * Settings::SIZE_GAME_MAP + position.x - 1);
	UpdatePosition(i);

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(i);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(i);
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

	MapEntity entity = *(map + (position.y * Settings::SIZE_GAME_MAP + (position.x + 1)));

	if (entity == MapEntity::Wall)
	{
		return delta;
	}

	int i = (position.y * Settings::SIZE_GAME_MAP + position.x + 1);
	UpdatePosition(i);

	if (entity == MapEntity::DBlock)
	{
		PutCollectable(i);
		return delta - 1;
	}

	if (entity > 3)
	{
		RemoveCollectable(i);
	}

	delta--;
	if (delta == 0)
		return 0;

	position.x++;
	return AskXRight(position, delta);
}

void ExplosionCalculator::PutCollectable(int i)
{

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
}
void ExplosionCalculator::RemoveCollectable(int i)
{
	*(map + i) = MapEntity::None;
}

void ExplosionCalculator::UpdatePosition(int i)
{
	*(mapExplosion + i) = 0.0f;

	if (*(mapBomb + i) >= 0.0f)
		*(mapBomb + i) = 3.001f;
}
#pragma endregion


#pragma region Public
void ExplosionCalculator::SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169])
{
	map = map2;
	mapExplosion = mapE;
	mapBomb = mapB;
}

ExplosionData ExplosionCalculator::GetData(int positionId, int range)
{
	Vector2i pos(positionId % Settings::SIZE_GAME_MAP, positionId / Settings::SIZE_GAME_MAP);

	ExplosionData entity;

	entity.centerId = pos;
	entity.xRight = range - AskXRight(pos, range);
	entity.xLeft = range - AskXLeft(pos, range);
	entity.yUp = range - AskYUp(pos, range);
	entity.yDown = range - AskYDown(pos, range);

	*(mapExplosion + (pos.y * Settings::SIZE_GAME_MAP + pos.x)) = 0.0f;

	return entity;
}
#pragma endregion





