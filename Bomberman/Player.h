#pragma once
#include "headersProject.h"

class Player
{
private:
	static int nbPlayer;

	int id;

	static Vector2i upRightCorner;
	static Vector2i downLeftCorner;

	static Color invicible;
	static Color normal;

	IMageUI image;

	Vector2f cartPosition;
	Vector2f direction;

	float animation = 0.f;
	float speed = 120.0f;

	float invincibilityTime = 0.0f;
	bool isInvicible = false;

	IntRect maskSprite;
	Vector2i directionAnimationV2i;


	MapEntity* map;

	int lives = 1;
	int range = 1;
	int bombs = 1;

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
	void ManageInvicibility();
	void GetDirection();
	void Move();

public:
	Player();
	~Player();

	void Reset();

	void SetMap(MapEntity*);
	int GetPositionIndex();
	int GetRange();
	int GetId();

	void AddSpeed();
	void AddBomb();
	void AddRange();
	void AddLife();



	bool AskRemoveBomb();
	
	void TakeDamage();
	void CheckDamageBomb(const ExplosionData&);
	void Update();
	void Draw();
};

