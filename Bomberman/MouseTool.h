#pragma once
#include "headersProject.h"

class MouseTool
{
	static MouseTool* instance;
	Vector2f globalPosition;


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

