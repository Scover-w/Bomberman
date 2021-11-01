#pragma once
#include "IMageUI.h"
#include "SoundManager.h"
#include "SoundType.h"

class Button : public IMageUI
{
protected:
	static Color white;
	static Color gray;
	static Color black;
	static Color invisible;
	static Color semiTransparent;

	bool isClicked = false;
	bool isHover = false;
	bool isReleased = true;
	bool isEnable = true;
	bool isActive = true;

	bool lastClick = true;

	void ResetState();
	bool DoesClick(bool);

public:

	Button();
	~Button();

	void Enable();
	void Disable();
	void SetActive(bool);

	bool DoesClick(Vector2f);
	
};

