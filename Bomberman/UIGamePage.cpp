#include "UIGamePage.h"


UIGamePage::UIGamePage(GamePage* p)
{
	page = p;

	LoadImages();
	LoadUIPositions();

	testText.setFont(SelectedFont::instance->GetFont());
	testText.setString("1");
	testText.setCharacterSize(50);
	testText.setFillColor(sf::Color::White);

	transparency = Color(255, 255, 255, 100);
	deltaItem = Vector2f(0.0f, 0.0f);
	deltaShadowNumber = Vector2f(10.0f, 0.0f);
}

UIGamePage::~UIGamePage()
{

}

void UIGamePage::LoadImages()
{
	Color semiTransparent(255, 255, 255, 100);

	blueGround.SetTexture("Images/UI/GamePage/BlueUIGround.png");
	blueGround.SetOrigin(0, -2);
	blueGround.SetColor(semiTransparent);

	redGround.SetTexture("Images/UI/GamePage/RedUIGround.png");
	redGround.SetOrigin(0, -2);
	redGround.SetColor(semiTransparent);

	greenGround.SetTexture("Images/UI/GamePage/GreenUIGround.png");
	greenGround.SetOrigin(0, -2);
	greenGround.SetColor(semiTransparent);

	yellowGround.SetTexture("Images/UI/GamePage/YellowUIGround.png");
	yellowGround.SetOrigin(0, -2);
	yellowGround.SetColor(semiTransparent);

	heartUI.SetTexture("Images/UI/GamePage/HeartUI.png");
	heartUI.SetOrigin(21, 0);

	bombUI.SetTexture("Images/UI/GamePage/BombUI.png");
	bombUI.SetOrigin(21, 0);

	lightUI.SetTexture("Images/UI/GamePage/LightUI.png");
	lightUI.SetOrigin(21, 0);

	powerUI.SetTexture("Images/UI/GamePage/PowerUI.png");
	powerUI.SetOrigin(21, 0);

	shadow.SetTexture("Images/UI/GamePage/ShadowUI.png");
	shadow.SetOrigin(21, 0);
}

void UIGamePage::LoadUIPositions()
{
	int bluePos[] = { -59, -58, -57, -56,  -46, -45, -44, -43 };
	int redPos[] = { 42, 55, 68, 81, 41, 54, 67, 80 };
	int greenPos[] = { 160, 139, 118, 97, 161, 140, 119 , 98 };
	int yellowPos[] = { 297, 298, 299, 300, 318, 319, 320, 321 };

	for (int i = 0; i < 8; i++)
	{
		groundUIBluePosition[i] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(bluePos[i]));
		groundUIRedPosition[i] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(redPos[i]));
		groundUIGreenPosition[i] = CustomMath::EnvPositionToIsoCoordF(greenPos[i]);
		groundUIYellowPosition[i] = CustomMath::EnvPositionToIsoCoordF(yellowPos[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		int* pos;
		switch (i % 4)
		{
			case 0:
				pos = bluePos;
				break;
			case 1:
				pos = redPos;
				break;
			case 2:
				pos = greenPos;
				break;
			default: // 3
				pos = yellowPos;
				break;
		}

		int deltaPos = (i < 4) ? 0 : 4;

		if (i % 4 < 2)
		{
			itemPosition[i * 4] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(*(pos + deltaPos)));
			itemPosition[i * 4 + 1] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(*(pos + deltaPos + 1)));
			itemPosition[i * 4 + 2] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(*(pos + deltaPos + 2)));
			itemPosition[i * 4 + 3] = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(*(pos + deltaPos + 3)));
		}
		else
		{
			itemPosition[i * 4] = CustomMath::EnvPositionToIsoCoordF(*(pos + deltaPos));
			itemPosition[i * 4 + 1] = CustomMath::EnvPositionToIsoCoordF(*(pos + deltaPos + 1));
			itemPosition[i * 4 + 2] = CustomMath::EnvPositionToIsoCoordF(*(pos + deltaPos + 2));
			itemPosition[i * 4 + 3] = CustomMath::EnvPositionToIsoCoordF(*(pos + deltaPos + 3));
		}

		Vector2f deltaV = (i < 4)? Vector2f(80.0f,0.0f) : Vector2f(70.0f,0.0f);

		itemPosition[i * 4] += deltaV;
		itemPosition[i * 4 + 1] += deltaV;
		itemPosition[i * 4 + 2] += deltaV;
		itemPosition[i * 4 + 3] += deltaV;
	}
}

void UIGamePage::Update()
{


}

void UIGamePage::Draw()
{
	float x;
	
	for (int i = 0; i < 8; i++)
	{
		blueGround.SetPosition(groundUIBluePosition[i]);
		blueGround.Draw();

		redGround.SetPosition(groundUIRedPosition[i]);
		redGround.Draw();

		greenGround.SetPosition(groundUIGreenPosition[i]);
		greenGround.Draw();

		yellowGround.SetPosition(groundUIYellowPosition[i]);
		yellowGround.Draw();
	}

	time = Timer::instance->GetTimeSpent();
	
	for (int i = 0; i < 16; i += 4)
	{
		x = CustomRandom::GetPseudoRandom(i);
		DrawShadowItem(x, i);
		SetDeltaItem(x);
		heartUI.SetPosition(itemPosition[i] + deltaItem);
		heartUI.Draw();

		x = CustomRandom::GetPseudoRandom(i + 1);
		DrawShadowItem(x, i + 1);
		SetDeltaItem(x);
		bombUI.SetPosition(itemPosition[i + 1] + deltaItem);
		bombUI.Draw();

		x = CustomRandom::GetPseudoRandom(i + 2);
		DrawShadowItem(x, i + 2);
		SetDeltaItem(x);
		lightUI.SetPosition(itemPosition[i + 2] + deltaItem);
		lightUI.Draw();


		x = CustomRandom::GetPseudoRandom(i + 3);
		DrawShadowItem(x, i + 3);
		SetDeltaItem(x);
		powerUI.SetPosition(itemPosition[i + 3] + deltaItem);
		powerUI.Draw();	
	}

	for (int i = 16; i < 32; i += 4)
	{
		x = CustomRandom::GetPseudoRandom(i);
		DrawShadowNumber(x, i);
		SetDeltaItem(x);
		testText.setPosition(itemPosition[i] + deltaItem);
		StaticWindow::window->draw(testText);
    
		x = CustomRandom::GetPseudoRandom(i + 1);
		DrawShadowNumber(x, i + 1);
		SetDeltaItem(x);
		testText.setPosition(itemPosition[i + 1] + deltaItem);
		StaticWindow::window->draw(testText);

		x = CustomRandom::GetPseudoRandom(i + 2);
		DrawShadowNumber(x, i + 2);
		SetDeltaItem(x);
		testText.setPosition(itemPosition[i + 2] + deltaItem);
		StaticWindow::window->draw(testText);

		x = CustomRandom::GetPseudoRandom(i + 3);
		DrawShadowNumber(x, i + 3);
		SetDeltaItem(x);
		testText.setPosition(itemPosition[i + 3] + deltaItem);
		StaticWindow::window->draw(testText);
	}
}

void UIGamePage::SetTransparency(float x)
{
	transparency.a = ((sin(x + time) + 1) * 0.5f * 0.4f + 0.3f) * 255.0f;
}

void UIGamePage::SetDeltaItem(float x)
{
	deltaItem.y = (sin(x + time) + 1) * 5.0f - 20.0f;
}

void UIGamePage::DrawShadowItem(float x, int i)
{
	SetTransparency(x);
	shadow.SetColor(transparency);
	shadow.SetPosition(itemPosition[i]);
	shadow.Draw();
}


void UIGamePage::DrawShadowNumber(float x, int i)
{
	SetTransparency(x);
	shadow.SetColor(transparency);
	shadow.SetPosition(itemPosition[i] + deltaShadowNumber);
	shadow.Draw();
}