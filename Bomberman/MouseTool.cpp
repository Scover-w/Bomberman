#include "MouseTool.h"

Vector2f MouseTool::GetIsoPositionMouse()
{
	Vector2i relativePosition = Mouse::getPosition(*StaticWindow::window);
	Vector2f globalPosition = StaticWindow::window->mapPixelToCoords(relativePosition);
	return globalPosition;
}


Vector2f MouseTool::GetCartPositionMouse()
{
	return CustomMath::IsometricToCartesian(GetIsoPositionMouse());
}

int MouseTool::GetIndexPositionMouse()
{
	Vector2f mousePosition = GetCartPositionMouse();

	if (mousePosition.x < 0 || mousePosition.y < 0 || mousePosition.x > 1469 || mousePosition.y > 1469)
		return -1;

	mousePosition.x /= Settings::CARTESIAN_ATOMIC_HEIGHT;
	mousePosition.y /= Settings::CARTESIAN_ATOMIC_HEIGHT;


	return ((int)mousePosition.y) * Settings::NB_HEIGHT_MAP + ((int)mousePosition.x);
}