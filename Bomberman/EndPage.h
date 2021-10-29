#pragma once
#include "headersProject.h"
#include "PhysicalButton.h"

class UIEndPage;

class EndPage
{
private:
	bool hasWin;

	UIEndPage* ui;

public:
	EndPage();
	~EndPage();

	void LoadPage();
	void Update();

	void ManageEvent();

	void MenuClick();
	void RestartClick();
};

