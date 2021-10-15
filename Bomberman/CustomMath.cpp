#include "CustomMath.h"

const float CustomMath::rotation = M_PI / 4.0f;

Vector2i CustomMath::PositionToCoord(int i)
{
	Vector2i coord;
	coord.y = i / Settings::NB_HEIGHT_MAP;
	coord.x = i - coord.y * Settings::NB_HEIGHT_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	return coord;
}

int CustomMath::CartCoordFToPosition(Vector2f coord)
{
	cout << "Cart to in : " << coord.x << ", " << coord.y << endl;
	return ((int)((int)coord.y / Settings::CARTESIAN_ATOMIC_HEIGHT)) * 13 + ((int)((int)coord.x / Settings::CARTESIAN_ATOMIC_HEIGHT));
}

Vector2f CustomMath::PositionToCartCoordF(int i)
{
	Vector2i coord;

	coord.y = i / Settings::NB_HEIGHT_MAP;
	coord.x = i - coord.y * Settings::NB_HEIGHT_MAP;
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT; 
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	Vector2f temp(coord);

	return temp;
}

Vector2f CustomMath::PositionToIsoCoordF(int i)
{
	return CartesianToIsometric(PositionToCartCoordF(i));
}

Vector2f CustomMath::CartesianToIsometric(Vector2f cart)
{
	Vector2f isoV;
	
	isoV.x = cart.x * cos(rotation) - cart.y * sin(rotation);
	isoV.y = cart.x * sin(rotation) + cart.y * cos(rotation);
	
	isoV.y /= 2.0f;
	isoV.y += Settings::Y_TRANSLATION_MAP;
	isoV.x += Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::NB_WIDTH_MAP / 2.0f * sqrt(2)) - Settings::X_TRANSLATION_MAP;

	return isoV;
}

Vector2f CustomMath::IsometricToCartesian(Vector2f iso)
{
	iso.y *= 2.0f;
	iso.y -= Settings::Y_TRANSLATION_MAP;
	iso.x -= Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::NB_WIDTH_MAP / 2.0f * sqrt(2)) - Settings::X_TRANSLATION_MAP;
	Vector2f cartV;
	cartV.x = iso.x * cos(-rotation) - iso.y * sin(-rotation);
	cartV.y = iso.y * cos(rotation) - iso.x * sin(rotation);

	return cartV;
}

Vector2f CustomMath::EnvCartesianToIsometric(Vector2f cart)
{
	// Verified
	Vector2f isoV;

	isoV.x = cart.x * cos(-rotation) - cart.y * sin(-rotation);
	isoV.y = cart.x * sin(-rotation) + cart.y * cos(-rotation);

	isoV.y /= 2.0f;
	isoV.y += Settings::Y_TRANSLATION_MAP;
	isoV.x += Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::NB_WIDTH_MAP  / 2.0f * sqrt(2)) - Settings::X_TRANSLATION_MAP;

	return isoV;
}

Vector2f CustomMath::EnvIsometricToCartesian(Vector2f iso)
{
	iso.y *= 2.0f;
	iso.y -= Settings::Y_TRANSLATION_MAP;
	iso.x -= Settings::CARTESIAN_ATOMIC_HEIGHT * (Settings::NB_WIDTH_MAP  / 2.0f * sqrt(2)) - Settings::X_TRANSLATION_MAP;
	Vector2f cartV;
	cartV.x = iso.x * cos(rotation) - iso.y * sin(rotation);
	cartV.y = iso.y * cos(-rotation) - iso.x * sin(-rotation);

	return cartV;
}

Vector2f CustomMath::EnvPositionToIsoCoordF(int i)
{
	// Verified
	Vector2i coord;

	coord.y = i / (Settings::NB_HEIGHT_MAP + 8);
	coord.x = i - coord.y * (Settings::NB_HEIGHT_MAP + 8);
	coord.x *= Settings::CARTESIAN_ATOMIC_HEIGHT;
	coord.y *= Settings::CARTESIAN_ATOMIC_HEIGHT;

	Vector2f temp(coord);

	return CartesianToIsometric(temp);
}