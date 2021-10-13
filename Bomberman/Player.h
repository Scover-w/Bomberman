#pragma once
#include "headersProject.h"

class Player
{
private:
	IMageUI image;

	Vector2f position;
	Vector2f direction;

	float animation = 0.f;
	float speed = 120.0f;

	IntRect maskSprite;
	Vector2i directionAnimationV2i;

	bool isAlive;

	void DeltaAnimation();
	void SetDirectionAnimationVector2i();
	int GetStateAnimationDeath();
	int GetStateAnimation();
	bool isDead();

public:
	Player();
	~Player();

	void GetDirection();
	void KillPlayer();
	void Move();
	void Draw();
};

