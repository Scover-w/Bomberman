#include "MouseTool.h"

MouseTool* MouseTool::instance;

MouseTool::MouseTool()
{
	instance = this;
}
MouseTool::~MouseTool()
{

}

Vector2f MouseTool::GetGlobalPosition()
{
	Vector2i relativePosition = Mouse::getPosition(*StaticWindow::window);
	Vector2f globalPosition = StaticWindow::window->mapPixelToCoords(relativePosition);
	MouseTool::instance->globalPositionV2f = globalPosition;

	return globalPosition;
}


Vector2f MouseTool::GM_GetCartPositionMouse()
{
	return CustomMath::GM_IsometricToCartesian(GetGlobalPosition());
}
int MouseTool::GM_GetIndexPositionMouse()
{
	Vector2f mousePosition = GM_GetCartPositionMouse();

	if (mousePosition.x < 0 || mousePosition.y < 0 || mousePosition.x > 1469 || mousePosition.y > 1469)
		return -1;

	mousePosition.x /= Settings::CARTESIAN_ATOMIC_HEIGHT;
	mousePosition.y /= Settings::CARTESIAN_ATOMIC_HEIGHT;


	return ((int)mousePosition.y) * Settings::SIZE_GAME_MAP + ((int)mousePosition.x);
}


Vector2f MouseTool::UM_GetCartPositionMouse()
{
	return CustomMath::UM_IsometricToCartesian(GetGlobalPosition());
}
int MouseTool::UM_GetIndexPositionMouse()
{
	Vector2f mousePosition = UM_GetCartPositionMouse();

	mousePosition.x /= Settings::CARTESIAN_ATOMIC_HEIGHT;
	mousePosition.y /= Settings::CARTESIAN_ATOMIC_HEIGHT;


	return ((int)mousePosition.y) * Settings::SIZE_UI_MAP + ((int)mousePosition.x);
}