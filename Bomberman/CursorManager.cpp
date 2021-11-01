#include "CursorManager.h"


CursorManager* CursorManager::instance;

CursorManager::CursorManager()
{
	instance = this;

	normalCursor.loadFromSystem(sf::Cursor::Arrow);
	handCursor.loadFromSystem(sf::Cursor::Hand);
}
CursorManager::~CursorManager()
{

}

void CursorManager::SetNormalCursor()
{
	StaticWindow::window->setMouseCursor(normalCursor);
}
void CursorManager::SetHandCursor()
{
	StaticWindow::window->setMouseCursor(handCursor);
}