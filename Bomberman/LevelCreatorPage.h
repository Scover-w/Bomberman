#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "MapEditor.h"
#include "MapDrawer.h"

class LevelCreatorPage
{
	Texture selectionT;
	Sprite selectionS;

	Texture unselectionT;
	Sprite unselectionS;

	Vector2i tempVector;

	MapEntity map[169]{ MapEntity::None };

	Texture groundT;
	Sprite groundS;

	Texture wallT;
	Sprite wallS;

	Texture mapEntitiesT[2];
	Sprite mapEntitiesS[2];

	bool isEditing;

	int selectedMapId;

	int selectedIndexs[4];

	int selectedMapEntity = 1;

	Color opaque;
	Color transparent;
	Color midtransparent;

	int unPlacableIndex[12] = { 0, 1, 13, 11, 12, 25, 143, 156, 157, 155, 166, 167 };

public:
	LevelCreatorPage();
	~LevelCreatorPage();

	void DrawBackEnv(bool);
	void SwitchEditing();
	bool CanEdit();
	void Update();

	void MousePressed(Event&);

	void ClickMap(Event&);
	void ClickUI(Event&);

	void DrawSelection();
	void ComputeMirrorSelection();

	int MirrorX(int);
	int MirrorY(int);

	void AddEntity();
	void RemoveEntity();

	bool IsPlacable();
};

