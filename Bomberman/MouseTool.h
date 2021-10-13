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
	static Vector2f GetCartPositionMouse();
	static int GetIndexPositionMouse();
};

