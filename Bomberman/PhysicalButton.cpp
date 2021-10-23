#include "PhysicalButton.h"

PhysicalButton::PhysicalButton() : Button()
{
	for (int i = 0; i < 8; i++)
	{
		idsMap[i] = -1;
	}
}

PhysicalButton::~PhysicalButton()
{

}

bool PhysicalButton::DoesClick(int id)
{
	if (idsMap[0] == id)
	{
		isHover = true;
		return true;
	}


	for (int i = 0; i < 8; i++)
	{
		if (id == -1)
			return false;

		//if(true)
		//return true;
	}

	return false;
}

void PhysicalButton::SetTextures(string normalT, string hoverT, string clickT)
{
	SetTexture(normalT);
	hoverImg.SetTexture(hoverT);
	clickImg.SetTexture(clickT);
}

void PhysicalButton::SetPositionId(int posId)
{
	idsMap[0] = posId;
	position = CustomMath::UM_PositionToIsoCoordF(posId);
	SetPosition(position);
	hoverImg.SetPosition(position);
}

void PhysicalButton::SetOrigin(Vector2f pos)
{
	Button::SetOrigin(pos);
	hoverImg.SetOrigin(pos);
	clickImg.SetOrigin(pos);
}

void PhysicalButton::SetOrigin(float x, float y)
{
	Vector2f pos = Vector2f(x, y);
	SetOrigin(pos);
}

void PhysicalButton::Draw()
{
	/*for (int i = 0; i < 8; i++)
	{
		if (idsMap[i] == -1)
			break;

		// Draw for each case
	}*/
	if (isHover)
		hoverImg.Draw();
	else
		Button::Draw();
}