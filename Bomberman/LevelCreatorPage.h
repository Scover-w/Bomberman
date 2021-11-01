#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "MapEditor.h"
#include "MapDrawer.h"
#include "CursorManager.h"

class UILevelCreatorPage;

class LevelCreatorPage
{
	UILevelCreatorPage* ui;

	IMageUI selectionImg;
	IMageUI unSelectionImg;
	IMageUI groundImg;
	IMageUI wallImg;
	IMageUI brickWallImg;

	Vector2i tempVectorV2i;

	MapEntity map[169]{ MapEntity::None };

	Color opaque;
	Color transparent;
	Color midtransparent;

	bool isEditing;

	int selectedMapId;
	int maxMapId;
	int selectedIndexs[4];

	int unPlacableIndex[12] = { 0, 1, 13, 11, 12, 25, 143, 156, 157, 155, 167, 168 };
	
	void LoadTextures();

	void ManageEvent();
	void MousePressed(Event&);
	void ClickMap(Event&);
	void ClickUI(Event&);

	void SwitchEditing();
	bool CanEdit();

	void DrawSelection();
	void ComputeMirrorSelection();

	int MirrorX(int);
	int MirrorY(int);

	void AddEntity();
	void RemoveEntity();

	bool IsPlacable();

public:
	LevelCreatorPage();
	~LevelCreatorPage();

	void UISaveClick();
	void UINextLevelClick();
	void UIPreviousLevelClick();
	void UISwitchModeClick();
	void UIBackMenu();
	void UICreateLevel();

	void LoadPage();
	void Update();
};

