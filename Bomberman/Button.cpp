#include "Button.h"

Color Button::white(255, 255, 255, 255);
Color Button::gray(200, 200, 200, 255);
Color Button::black(0, 0, 0, 255);
Color Button::invisible(255,255,255,0);
Color Button::semiTransparent(255, 255, 255, 100);

Button::Button() : IMageUI()
{

}

Button::~Button()
{

}

void Button::ResetState()
{
	isClicked = false;
	isHover = false;
	isReleased = true;
	isEnable = true;
	lastClick = true;
	isActive = true;
}

bool Button::DoesClick(bool isMouseOnIt)
{
	if (isMouseOnIt && Mouse::isButtonPressed(Mouse::Left) && !isClicked && !lastClick)
	{
		sprite.setColor(black);
		isClicked = true;
		isReleased = false;
	}
	else if (isMouseOnIt && !Mouse::isButtonPressed(Mouse::Left) && !isReleased)
	{
		sprite.setColor(gray);
		isReleased = true;
		isClicked = false;
		return true;
	}
	else if (!isMouseOnIt && !Mouse::isButtonPressed(Mouse::Left) && !isReleased)
	{
		isReleased = true;
		isClicked = false;
	}

	if (isMouseOnIt == false && isHover)
	{
		sprite.setColor(white);
		isHover = false;
		isClicked = false;
		CursorManager::instance->SetNormalCursor();
		return false;
	}

	if (isMouseOnIt == true && isHover == false)
	{
		sprite.setColor(gray);
		isHover = true;
		CursorManager::instance->SetHandCursor();
	}

	lastClick = Mouse::isButtonPressed(Mouse::Left);

	return false;
}

bool Button::DoesClick(Vector2f mousePosition)
{
	if (!isEnable || !isActive)
		return false;

	return DoesClick(sprite.getGlobalBounds().contains(mousePosition));
}

void Button::Enable()
{
	ResetState();

	if(isActive)
		sprite.setColor(white);
	else
		sprite.setColor(semiTransparent);

	
	isEnable = true;
}

void Button::Disable()
{
	isEnable = false;
	sprite.setColor(invisible);

}

void Button::SetActive(bool state)
{
	isActive = state;

	if (isEnable && !isActive)
		sprite.setColor(semiTransparent);
	else if (isEnable && isActive)
		sprite.setColor(white);
}