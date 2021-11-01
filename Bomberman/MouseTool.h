#pragma once
#include "headersProject.h"

class MouseTool
{
private:

	static MouseTool* instance;
	Vector2f globalPositionV2f;

public:
	MouseTool();
	~MouseTool();

	static Vector2f GetGlobalPosition();

	// GM : Game Map
	static Vector2f GM_GetCartPositionMouse();
	static int GM_GetIndexPositionMouse();

	// UM : UI Map
	static Vector2f UM_GetCartPositionMouse();
	static int UM_GetIndexPositionMouse();
};

