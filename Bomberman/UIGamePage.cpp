#include "UIGamePage.h"

UIGamePage::UIGamePage(GamePage* p)
{
	page = p;

	LoadImages();
	LoadUIPositions();

	valueItemsTxt.setFont(SelectedFont::instance->GetFont());
	valueItemsTxt.setCharacterSize(50);
	valueItemsTxt.setFillColor(sf::Color::White);

	transparency = Color(255, 255, 255, 100);
	deltaShadowNumberV2f = Vector2f(10.0f, 0.0f);

	deltaTextV2f = Vector2f(0.0f, 37.0f);
}

UIGamePage::~UIGamePage()
{

}


#pragma region Private
void UIGamePage::LoadImages()
{
	Color semiTransparent(255, 255, 255, 100);

	blueGroundImg.SetTexture("Images/UI/GamePage/BlueUIGround.png");
	blueGroundImg.SetOrigin(0, -39);
	blueGroundImg.SetColor(semiTransparent);

	redGroundImg.SetTexture("Images/UI/GamePage/RedUIGround.png");
	redGroundImg.SetOrigin(0, -39);
	redGroundImg.SetColor(semiTransparent);

	greenGroundImg.SetTexture("Images/UI/GamePage/GreenUIGround.png");
	greenGroundImg.SetOrigin(0, -39);
	greenGroundImg.SetColor(semiTransparent);

	yellowGroundImg.SetTexture("Images/UI/GamePage/YellowUIGround.png");
	yellowGroundImg.SetOrigin(0, -39);
	yellowGroundImg.SetColor(semiTransparent);

	heartUIImg.SetTexture("Images/UI/GamePage/HeartUI.png");
	heartUIImg.SetOrigin(21, -37);

	bombUIImg.SetTexture("Images/UI/GamePage/BombUI.png");
	bombUIImg.SetOrigin(21, -37);

	lightUIImg.SetTexture("Images/UI/GamePage/LightUI.png");
	lightUIImg.SetOrigin(21, -37);

	powerUIImg.SetTexture("Images/UI/GamePage/PowerUI.png");
	powerUIImg.SetOrigin(21, -37);

	shadowImg.SetTexture("Images/UI/GamePage/ShadowUI.png");
	shadowImg.SetOrigin(21, -37);
}
void UIGamePage::LoadUIPositions()
{
	int bluePos[] = { 424, 396, 368, 340, 425, 397, 369, 341 };
	int redPos[] = { 152, 153, 154, 155, 180, 181, 182, 183 };
	int greenPos[] = { 442, 414, 386, 358, 443, 415, 387, 359 };
	int yellowPos[] = { 628, 629, 630, 631, 656, 657, 658, 659 };

	for (int i = 0; i < 8; i++)
	{
		groundUIBluePositionV2f[i] = CustomMath::UM_PositionToIsoCoordF(bluePos[i]);
		groundUIRedPositionV2f[i] = CustomMath::UM_PositionToIsoCoordF(redPos[i]);
		groundUIGreenPositionV2f[i] = CustomMath::UM_PositionToIsoCoordF(greenPos[i]);
		groundUIYellowPositionV2f[i] = CustomMath::UM_PositionToIsoCoordF(yellowPos[i]);
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

		itemPosition[i * 4] = CustomMath::UM_PositionToIsoCoordF(*(pos + deltaPos));
		itemPosition[i * 4 + 1] = CustomMath::UM_PositionToIsoCoordF(*(pos + deltaPos + 1));
		itemPosition[i * 4 + 2] = CustomMath::UM_PositionToIsoCoordF(*(pos + deltaPos + 2));
		itemPosition[i * 4 + 3] = CustomMath::UM_PositionToIsoCoordF(*(pos + deltaPos + 3));

		Vector2f deltaV = (i < 4) ? Vector2f(80.0f, 0.0f) : Vector2f(70.0f, 0.0f);

		itemPosition[i * 4] += deltaV;
		itemPosition[i * 4 + 1] += deltaV;
		itemPosition[i * 4 + 2] += deltaV;
		itemPosition[i * 4 + 3] += deltaV;
	}
}

void UIGamePage::SetLifePlayerText(int id)
{
	switch (id)
	{
		case 0:
			valueItemsTxt.setString(to_string(player->GetLife()));
			break;
		case 1:
			valueItemsTxt.setString(to_string(bot1->GetLife()));
			break;
		case 2:
			valueItemsTxt.setString(to_string(bot2->GetLife()));
			break;
		case 3:
			valueItemsTxt.setString(to_string(bot3->GetLife()));
			break;
	}
}
void UIGamePage::SetBombPlayerText(int id)
{
	switch (id)
	{
		case 0:
			valueItemsTxt.setString(to_string(player->GetNbBomb()));
			break;
		case 1:
			valueItemsTxt.setString(to_string(bot1->GetNbBomb()));
			break;
		case 2:
			valueItemsTxt.setString(to_string(bot2->GetNbBomb()));
			break;
		case 3:
			valueItemsTxt.setString(to_string(bot3->GetNbBomb()));
			break;
	}
}
void UIGamePage::SetRangePlayerText(int id)
{
	switch (id)
	{
		case 0:
			valueItemsTxt.setString(to_string(player->GetRange()));
			break;
		case 1:
			valueItemsTxt.setString(to_string(bot1->GetRange()));
			break;
		case 2:
			valueItemsTxt.setString(to_string(bot2->GetRange()));
			break;
		case 3:
			valueItemsTxt.setString(to_string(bot3->GetRange()));
			break;
	}
}
void UIGamePage::SetSpeedPlayerText(int id)
{
	switch (id)
	{
		case 0:
			valueItemsTxt.setString(to_string(player->GetSpeed()));
			break;
		case 1:
			valueItemsTxt.setString(to_string(bot1->GetSpeed()));
			break;
		case 2:
			valueItemsTxt.setString(to_string(bot2->GetSpeed()));
			break;
		case 3:
			valueItemsTxt.setString(to_string(bot3->GetSpeed()));
			break;
	}
}

void UIGamePage::SetTransparency(float x)
{
	transparency.a = ((sin(x + time) + 1) * 0.5f * 0.4f + 0.3f) * 255.0f;
}
void UIGamePage::SetDeltaItem(float x)
{
	deltaItemV2f.y = (sin(x + time) + 1) * 5.0f - 20.0f;
}

void UIGamePage::DrawShadowItem(float x, int i)
{
	SetTransparency(x);
	shadowImg.SetColor(transparency);
	shadowImg.SetPosition(itemPosition[i]);
	shadowImg.Draw();
}
void UIGamePage::DrawShadowNumber(float x, int i)
{
	SetTransparency(x);
	shadowImg.SetColor(transparency);
	shadowImg.SetPosition(itemPosition[i] + deltaShadowNumberV2f);
	shadowImg.Draw();
}
#pragma endregion


#pragma region Public
void UIGamePage::SetPlayers(Player* p, BotPlayer* b1, BotPlayer* b2, BotPlayer* b3)
{
	player = p;
	bot1 = b1;
	bot2 = b2;
	bot3 = b3;
}

void UIGamePage::Update()
{

}
void UIGamePage::Draw()
{
	float x;

	for (int i = 0; i < 8; i++)
	{
		blueGroundImg.SetPosition(groundUIBluePositionV2f[i]);
		blueGroundImg.Draw();

		redGroundImg.SetPosition(groundUIRedPositionV2f[i]);
		redGroundImg.Draw();

		greenGroundImg.SetPosition(groundUIGreenPositionV2f[i]);
		greenGroundImg.Draw();

		yellowGroundImg.SetPosition(groundUIYellowPositionV2f[i]);
		yellowGroundImg.Draw();
	}

	time = Timer::instance->GetTimeSpent();

	for (int i = 0; i < 16; i += 4)
	{
		x = CustomRandom::GetPseudoRandom(i);
		DrawShadowItem(x, i);
		SetDeltaItem(x);
		heartUIImg.SetPosition(itemPosition[i] + deltaItemV2f);
		heartUIImg.Draw();

		x = CustomRandom::GetPseudoRandom(i + 1);
		DrawShadowItem(x, i + 1);
		SetDeltaItem(x);
		bombUIImg.SetPosition(itemPosition[i + 1] + deltaItemV2f);
		bombUIImg.Draw();

		x = CustomRandom::GetPseudoRandom(i + 2);
		DrawShadowItem(x, i + 2);
		SetDeltaItem(x);
		lightUIImg.SetPosition(itemPosition[i + 2] + deltaItemV2f);
		lightUIImg.Draw();


		x = CustomRandom::GetPseudoRandom(i + 3);
		DrawShadowItem(x, i + 3);
		SetDeltaItem(x);
		powerUIImg.SetPosition(itemPosition[i + 3] + deltaItemV2f);
		powerUIImg.Draw();
	}

	for (int i = 16; i < 32; i += 4)
	{
		x = CustomRandom::GetPseudoRandom(i);
		DrawShadowNumber(x, i);
		SetDeltaItem(x);
		SetLifePlayerText((i - 16) / 4);

		valueItemsTxt.setPosition(itemPosition[i] + deltaItemV2f + deltaTextV2f);
		StaticWindow::window->draw(valueItemsTxt);

		x = CustomRandom::GetPseudoRandom(i + 1);
		DrawShadowNumber(x, i + 1);
		SetDeltaItem(x);
		SetBombPlayerText((i - 16) / 4);
		valueItemsTxt.setPosition(itemPosition[i + 1] + deltaItemV2f + deltaTextV2f);
		StaticWindow::window->draw(valueItemsTxt);

		x = CustomRandom::GetPseudoRandom(i + 2);
		DrawShadowNumber(x, i + 2);
		SetDeltaItem(x);
		SetSpeedPlayerText((i - 16) / 4);
		valueItemsTxt.setPosition(itemPosition[i + 2] + deltaItemV2f + deltaTextV2f);
		StaticWindow::window->draw(valueItemsTxt);

		x = CustomRandom::GetPseudoRandom(i + 3);
		DrawShadowNumber(x, i + 3);
		SetDeltaItem(x);
		SetRangePlayerText((i - 16) / 4);
		valueItemsTxt.setPosition(itemPosition[i + 3] + deltaItemV2f + deltaTextV2f);
		StaticWindow::window->draw(valueItemsTxt);
	}
}
#pragma endregion


