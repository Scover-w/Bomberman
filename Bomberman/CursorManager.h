#pragma once
#include "headersProject.h"
class CursorManager
{
private:
	Cursor normalCursor;
	Cursor handCursor;

public:
	static CursorManager* instance;

	CursorManager();
	~CursorManager();

	void SetNormalCursor();
	void SetHandCursor();
};

