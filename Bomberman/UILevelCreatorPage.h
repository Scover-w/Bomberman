#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "LevelCreatorPage.h"
#include "PhysicalButton.h"

class UILevelCreatorPage
{
private:
	LevelCreatorPage* page;
	bool isEditing = false;
	bool isClickable = true;

	int selectedMapId;
	int maxMapId;

	Vector2f mousePosition;
	int mouseUIPositionId;

	IMageUI title;

	PhysicalButton nextPButton;
	PhysicalButton previousPButton;
	PhysicalButton backMenuPButton;
	PhysicalButton savePButton;
	PhysicalButton switchModePButton1;
	PhysicalButton switchModePButton2;
	PhysicalButton newLevelPButton;

	IMageUI borderLevel;

	Text levelText;	

public:
	UILevelCreatorPage(LevelCreatorPage*);
	~UILevelCreatorPage();
	void SetEditionMode();
	void SetNormalMode();
	void SetMaxMapId(int);
	void SetActualMapId(int);
	void Update();
	void Draw();
};

