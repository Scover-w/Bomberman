#pragma once
#include "headersProject.h"

class Player
{
protected:
	static int nbPlayer;
	static Player* player;

	static MapEntity* map;

	int id;

	static Vector2i upRightCornerV2i;
	static Vector2i downLeftCornerV2i;

	Vector2i directionAnimationV2i;
	IntRect maskSprite;

	static Color invicible;
	static Color normal;

	IMageUI image;
	IMageUI shadowImg;

	Vector2f cartPositionV2f;
	Vector2f directionV2f;

	float animation = 0.f;
	float speed = 120.0f;

	float invincibilityTime = 0.0f;
	bool isInvicible = false;

	int onBombId = -1;
	int lives = 1;
	int range = 1;
	int bombs = 1;

	int positionIndex;
	int futurPosPlayerId[4];

	bool hasMoved = false;
	bool isDead = false;

	void DeltaAnimation();
	void SetDirectionAnimationVector2i();

	int GetStateAnimation();
	int GetStateAnimationDeath();

	int GetDeltaXPlayer(int);
	int GetDeltaYPlayer(int);

	void GetFuturPosPlayer(Vector2f);
	void GetDirection();

	void ManageInvicibility();
	void CheckCollectable();
	void TakeDamage();
	void Move();

public:

	Player();
	~Player();

	void SetMap(MapEntity*);
	void SetOnBombId(int);

	bool IsDead();
	
	void ResetOnBombId(int);

	void AddSpeed();
	void AddBomb();
	void AddRange();
	void AddLife();

	int GetPositionIndex();
	int GetId();

	int GetSpeed();
	int GetNbBomb();
	int GetRange();
	int GetLife();

	bool AskRemoveBomb();
	
	void CheckDamageBomb(const ExplosionData&);

	void Reset();
	void Update();
	void Draw();
};

