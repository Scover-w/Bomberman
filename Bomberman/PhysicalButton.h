#pragma once
#include "IMageUI.h"
#include "Button.h"
#include "PhysicalButtonType.h"
#include "RotationType.h"

class PhysicalButton : public Button
{
private:

	IMageUI hoverImg;
	IMageUI clickImg;
	
	Vector2f position;

	Vector2f positions[8];

	PhysicalButtonType type;
	RotationType rotation;

	int width, height;
	int idOrigin;

	int idsMap[8];
	void SetIds(int);
	void ResetIds();
	void SetId(int, int);
	void SetOrigin(float, float);
	void SetTextures(string, string, string);

public:
	PhysicalButton();
	~PhysicalButton();
	bool DoesClick(int);
	void SetBasicProperties(int, PhysicalButtonType, RotationType);
	void Draw();
};
