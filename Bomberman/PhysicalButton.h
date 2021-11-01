#pragma once
#include "IMageUI.h"
#include "Button.h"
#include "PhysicalButtonType.h"
#include "RotationType.h"

class PhysicalButton : public Button
{
private:
	static Vector2f deltaClickV2f;

	IMageUI hoverImg;
	IMageUI clickImg;

	IMageUI textImg;
	
	Vector2f positionV2f;

	Vector2f positionsV2f[14];

	PhysicalButtonType typePBtn;
	RotationType rotationT;

	int width, height;
	int idOrigin;

	int idsMap[14];

	void SetId(int, int);
	void SetIds(int);
	void ResetIds();
	void SetOrigin(float, float);
	void SetTextures(string, string, string);

public:
	PhysicalButton();
	~PhysicalButton();

	void SetImgText(string);
	void SetOriginText(float, float);
	void SetBasicProperties(int, PhysicalButtonType, RotationType);
	
	void Enable();
	void Disable();
	void SetActive(bool);

	bool DoesClick(int);
	void Draw();
};
