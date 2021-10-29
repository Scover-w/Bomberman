#include "UIEndPage.h"
#include "MouseTool.h"

UIEndPage::UIEndPage(EndPage* p)
{
	page = p;

	menuBtn.SetBasicProperties(433, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	menuBtn.SetImgText("Images/UI/End/Menu.png");
	menuBtn.SetOriginText(20, -57);

	restartBtn.SetBasicProperties(349, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	restartBtn.SetImgText("Images/UI/End/Replay.png");
	restartBtn.SetOriginText(60, -35);

	groundImg.SetTexture("Images/UI/End/UIGround.png");
	groundImg.SetOrigin(0, -39);


	winImg.SetTexture("Images/UI/End/Won.png");
	winImg.SetPosition(CustomMath::UM_PositionToIsoCoordF(293) + Vector2f(56, 20));
	loseImg.SetTexture("Images/UI/End/Lost.png");
	loseImg.SetPosition(CustomMath::UM_PositionToIsoCoordF(293) + Vector2f(47, 17));
}

UIEndPage::~UIEndPage()
{

}

void UIEndPage::SetWin(bool hasWin)
{
	Color white(255, 255, 255, 255);
	Color transparent(255, 255, 255, 0);
	
	winImg.SetColor(hasWin? white : transparent);
	loseImg.SetColor(hasWin ? transparent : white);
}

void UIEndPage::DrawBackText()
{
	float valueColor1 = (sin(Timer::instance->GetTimeSpent() * 0.5f) + 1) / 2;
	float valueColor2 = (sin(Timer::instance->GetTimeSpent() * 0.2f) + 1) / 2;
	float valueColor3 = (sin(Timer::instance->GetTimeSpent() * 0.7f) + 1) / 2;
	multiColor = Color(valueColor1 * 255, valueColor2 * 255, valueColor3 * 255, 255);
	groundImg.SetColor(multiColor);
	for (int i = 264; i < 268; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			groundImg.SetPosition(CustomMath::UM_PositionToIsoCoordF(i + j * 28));
			groundImg.Draw();
		}
	}
}

void UIEndPage::Update()
{
	int mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();

	if (menuBtn.DoesClick(mouseUIPositionId))
		page->MenuClick();

	if (restartBtn.DoesClick(mouseUIPositionId))
		page->RestartClick();
}

void UIEndPage::Draw()
{
	DrawBackText();
	winImg.Draw();
	loseImg.Draw();
	menuBtn.Draw();
	restartBtn.Draw();
}