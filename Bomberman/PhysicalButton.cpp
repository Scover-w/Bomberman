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

void PhysicalButton::SetPosition(Vector2f pos)
{
	position = pos;
}

void PhysicalButton::SetOrigin(Vector2f pos)
{
	SetOrigin(pos);
	hoverImg.SetOrigin(pos);
	clickImg.SetOrigin(pos);
}

void PhysicalButton::Draw()
{
	for (int i = 0; i < 8; i++)
	{
		if (idsMap[i] == -1)
			break;

		// Draw for each case
	}
}