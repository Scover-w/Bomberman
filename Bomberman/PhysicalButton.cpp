#include "PhysicalButton.h"

Vector2f PhysicalButton::deltaClick = Vector2f(0.0f, 7.0f);

PhysicalButton::PhysicalButton() : Button()
{
	ResetIds();
	SetTextures("Images/UI/Button/PhysicalButton.png",
		"Images/UI/Button/PhysicalButtonHover.png",
		"Images/UI/Button/PhysicalButtonClick.png");

	SetOrigin(80.0f, 37.0f);
}

PhysicalButton::~PhysicalButton()
{

}

void PhysicalButton::ResetIds()
{
	for (int i = 0; i < 8; i++)
	{
		idsMap[i] = -1;
	}
}

void PhysicalButton::SetImgText(string url)
{
	textImg.SetTexture(url);
}

void PhysicalButton::SetOriginText(float x, float y)
{
	textImg.SetOrigin(x, y);
}

bool PhysicalButton::DoesClick(int id)
{
	if (!isEnable || !isActive)
		return false;

	bool isMouseOnIt = false;

	for (int i = 0; i < width; i++)
	{
		if (id >= (idOrigin + i * Settings::SIZE_UI_MAP) && id <= (idOrigin + i * Settings::SIZE_UI_MAP + height - 1))
		{
			isMouseOnIt = true;
		}
	}

	return Button::DoesClick(isMouseOnIt);
}
	

void PhysicalButton::SetTextures(string normalT, string hoverT, string clickT)
{
	SetTexture(normalT);
	hoverImg.SetTexture(hoverT);
	clickImg.SetTexture(clickT);
}

void PhysicalButton::SetId(int index, int pos)
{
	Vector2f posV = CustomMath::UM_PositionToIsoCoordF(pos);
	idsMap[index] = pos;
	positions[index] = posV;

	if (index == 0)
		textImg.SetPosition(posV);
}

void PhysicalButton::SetIds(int posId)
{
	ResetIds();
	idOrigin = posId;
	if (type == PhysicalButtonType::Square)
	{
		SetId(0, posId);
		width = 1;
		height = 1;
		return;
	}
	
	if (type == PhysicalButtonType::BigSquare)
	{
		width = 2;
		height = 2;
	}
	else if(type == PhysicalButtonType::Rectangle3)
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 3;
		width = (rotation == RotationType::Horizontal) ? 3 : 2;
	}
	else if(type == PhysicalButtonType::Rectangle4)
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 4;
		width = (rotation == RotationType::Horizontal) ? 4 : 2;
	}
	else if (type == PhysicalButtonType::Rectangle5)
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 5;
		width = (rotation == RotationType::Horizontal) ? 5 : 2;
	}
	else if (type == PhysicalButtonType::Rectangle6)
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 6;
		width = (rotation == RotationType::Horizontal) ? 6 : 2;
	}
	else
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 7;
		width = (rotation == RotationType::Horizontal) ? 7 : 2;
	}
	
	int cursorIndex = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j+= 1)
		{
			SetId(cursorIndex, posId + i + j * Settings::SIZE_UI_MAP);
			cursorIndex++;
		}
	}
}

void PhysicalButton::SetBasicProperties(int posId, PhysicalButtonType typ, RotationType rot)
{
	type = typ;
	rotation = rot;
	SetIds(posId);
	position = CustomMath::UM_PositionToIsoCoordF(posId);
	SetPosition(position);
	hoverImg.SetPosition(position);
}


void PhysicalButton::SetOrigin(float x, float y)
{
	Button::SetOrigin(x, y);
	hoverImg.SetOrigin(x, y);
	clickImg.SetOrigin(x, y);
}

void PhysicalButton::Enable()
{
	ResetState();

	Color& color = (isActive) ? white : semiTransparent;

	sprite.setColor(color);
	hoverImg.SetColor(color);
	clickImg.SetColor(color);
	textImg.SetColor(color);
	isEnable = true;
}

void PhysicalButton::Disable()
{
	ResetState();
	isEnable = false;

	sprite.setColor(invisible);
	hoverImg.SetColor(invisible);
	clickImg.SetColor(invisible);
	textImg.SetColor(invisible);
}

void PhysicalButton::Draw()
{
	if (!isEnable)
		return;

	int max = height * width;

	for (int i = 0; i < max; i++)
	{
		if (idsMap[i] == -1)
			break;

		if (isClicked)
		{
			clickImg.SetPosition(positions[i]);
			clickImg.Draw();
		}
		else if(isHover)
		{
			hoverImg.SetPosition(positions[i]);
			hoverImg.Draw();
		}
		else
		{
			SetPosition(positions[i]);
			Button::Draw();
		}
	}	
	if (isClicked)
	{
		textImg.SetPosition(positions[0] + deltaClick);
	}
	else
	{
		textImg.SetPosition(positions[0]);
	}
	textImg.Draw();
}

void PhysicalButton::SetActive(bool state)
{
	isActive = state;

	if (isEnable && !isActive)
	{ 
		hoverImg.SetColor(semiTransparent);
		clickImg.SetColor(semiTransparent);
		textImg.SetColor(semiTransparent);
		Button::SetActive(state);
	}
	else if (isEnable && isActive)
	{
		hoverImg.SetColor(white);
		clickImg.SetColor(white);
		textImg.SetColor(white);
		Button::SetActive(state);
	}
}