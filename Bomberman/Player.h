#pragma once
#include "headersProject.h"

class Player
{
private:
	Sprite sprite;
	Texture texture;

	Vector2f position;
	Vector2f direction;

	float animation = 0.f;
	float speed = 120.0f;
	bool keys[4] = { false, false, false, false };

	IntRect maskSprite;
	Vector2i directionAnimationV2i;

	bool isAlive;

	void DeltaAnimation();

public:
	Player();
	~Player();

	void KeyManager(Event& e);

	void SetDirectionAnimationVector2i();
	int GetStateAnimation();
	int GetStateAnimationDeath();
	void GetDirection();

	void KillPlayer();
	bool isDead();

	void Move();

	void Draw();

	
};

