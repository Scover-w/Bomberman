#include "CustomMath.h"

const float CustomMath::rotation = M_PI / 4.0f;

#pragma region GM_GAMEMAP
Vector2i CustomMath::GM_PositionToCoord(int i)
{
	Vector2i coord;
	coord.y = i / Settings::SIZE_GAME_MAP;
	coord.x = i - coord.y * Settings::SIZE_GAME_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	return coord;
}
int CustomMath::GM_CartCoordFToPosition(Vector2f coord)
{
	return ((int)((int)coord.y / Settings::CARTESIAN_ATOMIC_HEIGHT)) * Settings::SIZE_GAME_MAP + ((int)((int)coord.x / Settings::CARTESIAN_ATOMIC_HEIGHT));
}

Vector2f CustomMath::GM_PositionToCartCoordF(int i)
{
	Vector2i coord;

	coord.y = i / Settings::SIZE_GAME_MAP;
	coord.x = i - coord.y * Settings::SIZE_GAME_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	Vector2f temp(coord);

	return temp;
}
Vector2f CustomMath::GM_PositionToIsoCoordF(int i)
{
	return GM_CartesianToIsometric(GM_PositionToCartCoordF(i));
}

Vector2f CustomMath::GM_CartesianToIsometric(Vector2f cart)
{
	Vector2f isoV;

	isoV.x = cart.x * cos(rotation) - cart.y * sin(rotation);
	isoV.y = cart.x * sin(rotation) + cart.y * cos(rotation);

	isoV.y /= 2.0f;
	isoV.y += Settings::GAME_TRANSLATION_MAP.y;
	isoV.x += Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::SIZE_GAME_MAP / 2.0f * sqrt(2)) - Settings::GAME_TRANSLATION_MAP.x;

	return isoV;
}
Vector2f CustomMath::GM_IsometricToCartesian(Vector2f iso)
{
	iso.y -= Settings::GAME_TRANSLATION_MAP.y;
	iso.x -= Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::SIZE_GAME_MAP / 2.0f * sqrt(2)) - Settings::GAME_TRANSLATION_MAP.x;
	iso.y *= 2.0f;
	Vector2f cartV;
	cartV.x = iso.x * cos(-rotation) - iso.y * sin(-rotation);
	cartV.y = iso.y * cos(rotation) - iso.x * sin(rotation);

	return cartV;
}
#pragma endregion

#pragma region UM_UIMAP
Vector2i CustomMath::UM_PositionToCoord(int i)
{
	Vector2i coord;
	coord.y = i / Settings::SIZE_UI_MAP;
	coord.x = i - coord.y * Settings::SIZE_UI_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	return coord;
}
int CustomMath::UM_CartCoordFToPosition(Vector2f coord)
{
	return ((int)((int)coord.y / Settings::CARTESIAN_ATOMIC_HEIGHT)) * Settings::SIZE_UI_MAP + ((int)((int)coord.x / Settings::CARTESIAN_ATOMIC_HEIGHT));
}

Vector2f CustomMath::UM_PositionToCartCoordF(int i)
{
	Vector2i coord;

	coord.y = i / Settings::SIZE_UI_MAP;
	coord.x = i - coord.y * Settings::SIZE_UI_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	Vector2f temp(coord);

	return temp;
}
Vector2f CustomMath::UM_PositionToIsoCoordF(int i)
{
	return UM_CartesianToIsometric(UM_PositionToCartCoordF(i));
}

Vector2f CustomMath::UM_CartesianToIsometric(Vector2f cart)
{
	Vector2f isoV;

	isoV.x = cart.x * cos(rotation) - cart.y * sin(rotation);
	isoV.y = cart.x * sin(rotation) + cart.y * cos(rotation);

	isoV.y /= 2.0f;
	isoV.y += Settings::UI_TRANSLATION_MAP.y;
	isoV.x += Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::SIZE_GAME_MAP / 2.0f * sqrt(2)) - Settings::UI_TRANSLATION_MAP.x;

	return isoV;
}
Vector2f CustomMath::UM_IsometricToCartesian(Vector2f iso)
{
	iso.y -= Settings::UI_TRANSLATION_MAP.y;
	iso.x -= Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::SIZE_GAME_MAP / 2.0f * sqrt(2)) - Settings::UI_TRANSLATION_MAP.x;
	iso.y *= 2.0f;
	Vector2f cartV;
	cartV.x = iso.x * cos(-rotation) - iso.y * sin(-rotation);
	cartV.y = iso.y * cos(rotation) - iso.x * sin(rotation);

	return cartV;
}
#pragma endregion


