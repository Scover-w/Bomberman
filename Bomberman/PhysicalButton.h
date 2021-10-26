#pragma once
#include "IMageUI.h"
#include "Button.h"
#include "PhysicalButtonType.h"
#include "RotationType.h"

class PhysicalButton : public Button
{
private:
	static Vector2f deltaClick;
	IMageUI hoverImg;
	IMageUI clickImg;

	IMageUI textImg;
	
	Vector2f position;

	Vector2f positions[14];

	PhysicalButtonType type;
	RotationType rotation;

	int width, height;
	int idOrigin;

	int idsMap[14];
	void SetIds(int);
	void ResetIds();
	void SetId(int, int);
	void SetOrigin(float, float);
	void SetTextures(string, string, string);

public:
	PhysicalButton();
	~PhysicalButton();
	bool DoesClick(int);
	void SetOriginText(float, float);
	void SetImgText(string);
	void SetBasicProperties(int, PhysicalButtonType, RotationType);
	void Enable();
	void Disable();
	void Draw();
};
