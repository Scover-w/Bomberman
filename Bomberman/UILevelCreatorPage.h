#pragma once
#include "headersProject.h"
#include "MouseTool.h"
#include "Button.h"
#include "LevelCreatorPage.h"

class UILevelCreatorPage
{
private:
	LevelCreatorPage* page;
	bool isEditing = false;
	bool isClickable = true;

	int selectedMapId;
	int maxMapId;

	Vector2f mousePosition;

	IMageUI title;

	Button nextButton;
	Button previousButton;
	Button backMenuButton;
	Button saveButton;
	Button switchModeButton1;
	Button switchModeButton2;
	Button newLevelButton;

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

