#pragma once
#include "headersProject.h"

class Player
{
private:

	static Vector2i upRightCorner;
	static Vector2i downLeftCorner;

	IMageUI image;

	Vector2f cartPosition;
	Vector2f direction;

	float animation = 0.f;
	float speed = 120.0f;

	IntRect maskSprite;
	Vector2i directionAnimationV2i;

	MapEntity* map;

	bool isAlive = true;

	int positionIndex;
	int futurPosPlayerId[4];

	void DeltaAnimation();
	void SetDirectionAnimationVector2i();
	int GetStateAnimationDeath();
	int GetStateAnimation();
	bool isDead();
	int GetDeltaXPlayer(int);
	int GetDeltaYPlayer(int);
	void GetFuturPosPlayer(Vector2f);

public:
	Player();
	~Player();

	void SetMap(MapEntity*);
	int GetPositionIndex();
	void ResetPosition();
	void GetDirection();
	void KillPlayer();
	void Move();
	void Draw();
};

