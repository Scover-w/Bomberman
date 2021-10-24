#include "PhysicalButton.h"

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
	idsMap[index] = pos;
	positions[index] = CustomMath::UM_PositionToIsoCoordF(pos);
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
	else // Rectangle
	{
		height = (rotation == RotationType::Horizontal) ? 2 : 4;
		width = (rotation == RotationType::Horizontal) ? 4 : 2;
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

void PhysicalButton::Draw()
{
	for (int i = 0; i < 8; i++)
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
}