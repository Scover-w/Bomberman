#pragma once
#include "headersProject.h"

class UILevelCreatorPage
{
private:
	IMageUI title;
	bool isEditing = false;
public:
	UILevelCreatorPage();
	~UILevelCreatorPage();
	void Draw();
};

