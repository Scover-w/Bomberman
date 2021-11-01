#pragma once
#include "headersProject.h"
#include "Player.h"
#include "CustomRandom.h"
#include "BotPlayer.h"

class MapDrawer
{
private:

	Player* player;
	BotPlayer* bot1;
	BotPlayer* bot2;
	BotPlayer* bot3;

	MapEntity* map;

	IMageUI destructableImgs[14];
	IMageUI wallImgs[4];
	IMageUI groundImgs[16];

	IMageUI wallEnvImg;

	IMageUI bombImg;

	IMageUI explosionImg;
	IntRect explosionMaskSprite;

	IMageUI heartImg;
	IMageUI speedImg;
	IMageUI bombImg2;
	IMageUI powerImg;

	IMageUI shadowItemImg;

	Color transparency;

	float* mapExplosion;
	float* mapBomb;
	float time;

	int selectedWall;
	int selectedDestructable;
	int selectedGround;

	float GetDeltaAnimItem(int);

	void DrawShadowItem(Vector2f&, float);
	void DrawWallEnv(int);
	void DrawGround(int);

public:
	static MapDrawer* instance;

	MapDrawer();
	~MapDrawer();

	void SetMap(MapEntity(&map2)[169]);
	void SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169]);
	void SetPlayers(Player*,BotPlayer*,BotPlayer*, BotPlayer*);

	void DrawEnv(bool);
	void DrawArenaInWall();
	void DrawAnimatedArenaInWall(const float&);
	void DrawArenaInGround();
	void DrawEditor();
	void Draw();
};

