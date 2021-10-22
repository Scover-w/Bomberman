#pragma once
#include "headersProject.h"
#include "Player.h"
#include "CustomRandom.h"

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

	MapEntity* map;
	float* mapExplosion;
	float* mapBomb;
	float time;

	Color transparency;


	float GetDeltaAnimItem(int);
	void DrawShadowItem(Vector2f&, float);


public:
	static MapDrawer* instance;
	MapDrawer();
	~MapDrawer();
	void SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169]);
	void SetMap(MapEntity(&map2)[169]);
	void SetPlayer(Player*);
	void DrawEnv(bool);
	void Draw();
	void DrawEditor();
};

