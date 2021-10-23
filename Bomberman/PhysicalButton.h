#pragma once
#include "IMageUI.h"
#include "Button.h"

class PhysicalButton : public Button
{
private:

	IMageUI hoverImg;
	IMageUI clickImg;
	
	Vector2f position;

	Vector2f positions;

	int idsMap[8];

public:
	PhysicalButton();
	~PhysicalButton();
	bool DoesClick(int);
	void SetTextures(string, string, string);
	void SetPositionId(int);
	void SetOrigin(Vector2f);
	void SetOrigin(float, float);
	void Draw();
};
