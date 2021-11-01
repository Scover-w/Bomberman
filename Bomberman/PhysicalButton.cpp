#include "PhysicalButton.h"

Vector2f PhysicalButton::deltaClickV2f = Vector2f(0.0f, 7.0f);

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

#pragma region Private
void PhysicalButton::SetId(int index, int pos)
{
	Vector2f posV = CustomMath::UM_PositionToIsoCoordF(pos);
	idsMap[index] = pos;
	positionsV2f[index] = posV;

	if (index == 0)
		textImg.SetPosition(posV);
}
void PhysicalButton::SetIds(int posId)
{
	ResetIds();
	idOrigin = posId;
	if (typePBtn == PhysicalButtonType::Square)
	{
		SetId(0, posId);
		width = 1;
		height = 1;
		return;
	}

	if (typePBtn == PhysicalButtonType::BigSquare)
	{
		width = 2;
		height = 2;
	}
	else if (typePBtn == PhysicalButtonType::Rectangle3)
	{
		height = (rotationT == RotationType::Horizontal) ? 2 : 3;
		width = (rotationT == RotationType::Horizontal) ? 3 : 2;
	}
	else if (typePBtn == PhysicalButtonType::Rectangle4)
	{
		height = (rotationT == RotationType::Horizontal) ? 2 : 4;
		width = (rotationT == RotationType::Horizontal) ? 4 : 2;
	}
	else if (typePBtn == PhysicalButtonType::Rectangle5)
	{
		height = (rotationT == RotationType::Horizontal) ? 2 : 5;
		width = (rotationT == RotationType::Horizontal) ? 5 : 2;
	}
	else if (typePBtn == PhysicalButtonType::Rectangle6)
	{
		height = (rotationT == RotationType::Horizontal) ? 2 : 6;
		width = (rotationT == RotationType::Horizontal) ? 6 : 2;
	}
	else
	{
		height = (rotationT == RotationType::Horizontal) ? 2 : 7;
		width = (rotationT == RotationType::Horizontal) ? 7 : 2;
	}

	int cursorIndex = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j += 1)
		{
			SetId(cursorIndex, posId + i + j * Settings::SIZE_UI_MAP);
			cursorIndex++;
		}
	}
}
void PhysicalButton::ResetIds()
{
	for (int i = 0; i < 8; i++)
	{
		idsMap[i] = -1;
	}
}
void PhysicalButton::SetOrigin(float x, float y)
{
	Button::SetOrigin(x, y);
	hoverImg.SetOrigin(x, y);
	clickImg.SetOrigin(x, y);
}
void PhysicalButton::SetTextures(string normalT, string hoverT, string clickT)
{
	SetTexture(normalT);
	hoverImg.SetTexture(hoverT);
	clickImg.SetTexture(clickT);
}
#pragma endregion

#pragma region Public
void PhysicalButton::SetImgText(string url)
{
	textImg.SetTexture(url);
}
void PhysicalButton::SetOriginText(float x, float y)
{
	textImg.SetOrigin(x, y);
}
void PhysicalButton::SetBasicProperties(int posId, PhysicalButtonType typ, RotationType rot)
{
	typePBtn = typ;
	rotationT = rot;
	SetIds(posId);
	positionV2f = CustomMath::UM_PositionToIsoCoordF(posId);
	SetPosition(positionV2f);
	hoverImg.SetPosition(positionV2f);
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
			clickImg.SetPosition(positionsV2f[i]);
			clickImg.Draw();
		}
		else if (isHover)
		{
			hoverImg.SetPosition(positionsV2f[i]);
			hoverImg.Draw();
		}
		else
		{
			SetPosition(positionsV2f[i]);
			Button::Draw();
		}
	}
	if (isClicked)
	{
		textImg.SetPosition(positionsV2f[0] + deltaClickV2f);
	}
	else
	{
		textImg.SetPosition(positionsV2f[0]);
	}
	textImg.Draw();
}
#pragma endregion


