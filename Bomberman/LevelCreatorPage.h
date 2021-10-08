#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "MapEditor.h"
#include "MapDrawer.h"
#include "CursorManager.h"
#include "UILevelCreatorPage.h"

class LevelCreatorPage
{
	IMageUI selectionImg;
	IMageUI unSelectionImg;
	IMageUI groundImg;
	IMageUI wallImg;
	IMageUI mapEntitiesImg[2];

	Vector2i tempVector;

	MapEntity map[169]{ MapEntity::None };

	

	bool isEditing;

	int selectedMapId;

	int selectedIndexs[4];

	int selectedMapEntity = 1;

	Color opaque;
	Color transparent;
	Color midtransparent;

	UILevelCreatorPage ui;

	int unPlacableIndex[12] = { 0, 1, 13, 11, 12, 25, 143, 156, 157, 155, 166, 167 };

public:
	LevelCreatorPage();
	~LevelCreatorPage();

	void DrawBackEnv(bool);
	void SwitchEditing();
	bool CanEdit();
	void Update();

	void ManageEvent();

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

