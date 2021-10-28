#pragma once
#include "headersProject.h"
#include "Player.h"
#include "CustomRandom.h"
#include "BotPlayer.h"

class MapDrawer
{
private:
	IMageUI destructables[14];
	IMageUI walls[4];
	IMageUI grounds[16];

	IMageUI wallEnvImg;

	IMageUI bombImg;

	IMageUI explosionImg;
	IntRect explosionMaskSprite;

	IMageUI heartImg;
	IMageUI speedImg;
	IMageUI bombImg2;
	IMageUI powerImg;

	IMageUI shadowItem;

	int selectedWall;
	int selectedDestructable;
	int selectedGround;

	Player* player;
	BotPlayer* bot1;
	BotPlayer* bot2;
	BotPlayer* bot3;

	MapEntity* map;
	float* mapExplosion;
	float* mapBomb;
	float time;

	Color transparency;


	float GetDeltaAnimItem(int);
	void DrawShadowItem(Vector2f&, float);
	void DrawWallEnv(int);
	void DrawGround(int);

public:
	static MapDrawer* instance;
	MapDrawer();
	~MapDrawer();
	void SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169]);
	void SetMap(MapEntity(&map2)[169]);
	void SetPlayers(Player*,BotPlayer*,BotPlayer*, BotPlayer*);
	void DrawEnv(bool);
	void DrawArenaInWall();
	void DrawAnimatedArenaInWall(const float&);
	void DrawArenaInGround();
	void Draw();
	void DrawEditor();
};

