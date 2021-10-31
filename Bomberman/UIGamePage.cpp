#include "UIGamePage.h"


UIGamePage::UIGamePage(GamePage* p)
{
	page = p;

	LoadImages();
	LoadUIPositions();

	valueItems.setFont(SelectedFont::instance->GetFont());
	valueItems.setCharacterSize(50);
	valueItems.setFillColor(sf::Color::White);

	transparency = Color(255, 255, 255, 100);
	deltaShadowNumber = Vector2f(10.0f, 0.0f);

	deltaText = Vector2f(0.0f, 37.0f);
}

UIGamePage::~UIGamePage()
{

}

void UIGamePage::SetPlayers(Player* p, BotPlayer* b1, BotPlayer* b2, BotPlayer* b3)
{
	player = p;
	bot1 = b1;
	bot2 = b2;
	bot3 = b3;
}

void UIGamePage::LoadImages()
{
	Color semiTransparent(255, 255, 255, 100);

	blueGround.SetTexture("Images/UI/GamePage/BlueUIGround.png");
	blueGround.SetOrigin(0, -39);
	blueGround.SetColor(semiTransparent);

	redGround.SetTexture("Images/UI/GamePage/RedUIGround.png");
	redGround.SetOrigin(0, -39);
	redGround.SetColor(semiTransparent);

	greenGround.SetTexture("Images/UI/GamePage/GreenUIGround.png");
	greenGround.SetOrigin(0, -39);
	greenGround.SetColor(semiTransparent);

	yellowGround.SetTexture("Images/UI/GamePage/YellowUIGround.png");
	yellowGround.SetOrigin(0, -39);
	yellowGround.SetColor(semiTransparent);

	heartUI.SetTexture("Images/UI/GamePage/HeartUI.png");
	heartUI.SetOrigin(21, -37);

	bombUI.SetTexture("Images/UI/GamePage/BombUI.png");
	bombUI.SetOrigin(21, -37);

	lightUI.SetTexture("Images/UI/GamePage/LightUI.png");
	lightUI.SetOrigin(21, -37);

	powerUI.SetTexture("Images/UI/GamePage/PowerUI.png");
	powerUI.SetOrigin(21, -37);

	shadow.SetTexture("Images/UI/GamePage/ShadowUI.png");
	shadow.SetOrigin(21, -37);
}

void UIGamePage::LoadUIPositions()
{
	int bluePos[] = { 424, 396, 368, 340, 425, 397, 369, 341 };
	int redPos[] = { 152, 153, 154, 155, 180, 181, 182, 183 };
	int greenPos[] = { 442, 414, 386, 358, 443, 415, 387, 359 };
	int yellowPos[] = { 628, 629, 630, 631, 656, 657, 658, 659 };

	for (int i = 0; i < 8; i++)
	{
		groundUIBluePosition[i] = CustomMath::UM_PositionToIsoCoordF(bluePos[i]);
		groundUIRedPosition[i] = CustomMath::UM_PositionToIsoCoordF(redPos[i]);
		groundUIGreenPosition[i] = CustomMath::UM_PositionToIsoCoordF(greenPos[i]);
		groundUIYellowPosition[i] = CustomMath::UM_PositionToIsoCoordF(yellowPos[i]);
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

void UIGamePage::SetLifePlayerText(int id)
{
	switch (id)
	{
		case 0:
			valueItems.setString(to_string(player->GetLife()));
			break;
		case 1:
			valueItems.setString(to_string(bot1->GetLife()));
			break;
		case 2:
			valueItems.setString(to_string(bot2->GetLife()));
			break;
		case 3:
			valueItems.setString(to_string(bot3->GetLife()));
			break;
	}
}
void UIGamePage::SetBombPlayerText(int id)
{
	switch (id)
	{
	case 0:
		valueItems.setString(to_string(player->GetNbBomb()));
		break;
	case 1:
		valueItems.setString(to_string(bot1->GetNbBomb()));
		break;
	case 2:
		valueItems.setString(to_string(bot2->GetNbBomb()));
		break;
	case 3:
		valueItems.setString(to_string(bot3->GetNbBomb()));
		break;
	}
}
void UIGamePage::SetRangePlayerText(int id)
{
	switch (id)
	{
	case 0:
		valueItems.setString(to_string(player->GetRange()));
		break;
	case 1:
		valueItems.setString(to_string(bot1->GetRange()));
		break;
	case 2:
		valueItems.setString(to_string(bot2->GetRange()));
		break;
	case 3:
		valueItems.setString(to_string(bot3->GetRange()));
		break;
	}
}
void UIGamePage::SetSpeedPlayerText(int id)
{
	switch (id)
	{
	case 0:
		valueItems.setString(to_string(player->GetSpeed()));
		break;
	case 1:
		valueItems.setString(to_string(bot1->GetSpeed()));
		break;
	case 2:
		valueItems.setString(to_string(bot2->GetSpeed()));
		break;
	case 3:
		valueItems.setString(to_string(bot3->GetSpeed()));
		break;
	}
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
		SetLifePlayerText((i - 16) / 4);
		
		valueItems.setPosition(itemPosition[i] + deltaItem + deltaText);
		StaticWindow::window->draw(valueItems);
    
		x = CustomRandom::GetPseudoRandom(i + 1);
		DrawShadowNumber(x, i + 1);
		SetDeltaItem(x);
		SetBombPlayerText((i - 16) / 4);
		valueItems.setPosition(itemPosition[i + 1] + deltaItem + deltaText);
		StaticWindow::window->draw(valueItems);

		x = CustomRandom::GetPseudoRandom(i + 2);
		DrawShadowNumber(x, i + 2);
		SetDeltaItem(x);
		SetSpeedPlayerText((i - 16) / 4);
		valueItems.setPosition(itemPosition[i + 2] + deltaItem + deltaText);
		StaticWindow::window->draw(valueItems);

		x = CustomRandom::GetPseudoRandom(i + 3);
		DrawShadowNumber(x, i + 3);
		SetDeltaItem(x);
		SetRangePlayerText((i - 16) / 4);
		valueItems.setPosition(itemPosition[i + 3] + deltaItem + deltaText);
		StaticWindow::window->draw(valueItems);
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