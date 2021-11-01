#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "LevelCreatorPage.h"
#include "PhysicalButton.h"

class UILevelCreatorPage
{
private:
	LevelCreatorPage* page;

	IMageUI titleImg;
	IMageUI borderLevelImg;

	PhysicalButton nextPBtn;
	PhysicalButton previousPBtn;
	PhysicalButton backMenuPBtn;
	PhysicalButton savePBtn;
	PhysicalButton switchModePBtn1;
	PhysicalButton switchModePBtn2;
	PhysicalButton newLevelPBtn;

	Text levelTxt;	

	int mouseUIPositionId;


	bool isEditing = false;
	bool isClickable = true;

	int selectedMapId;
	int maxMapId;

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

