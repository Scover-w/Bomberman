#pragma once
#include "headersProject.h"
#include "PhysicalButton.h"

class UIEndPage;

class EndPage
{
private:

	UIEndPage* ui;

	bool hasWin;

	void ManageEvent();

public:

	EndPage();
	~EndPage();

	void MenuClick();
	void RestartClick();

	void LoadPage();
	void Update();


	
};

