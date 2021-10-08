#include "UILevelCreatorPage.h"

UILevelCreatorPage::UILevelCreatorPage()
{
	title.SetTexture("Images/UI/ModeEditeur.png");
	title.SetPosition(40, 250);
	title.SetRotation(-26.5);
}

UILevelCreatorPage::~UILevelCreatorPage()
{

}

void UILevelCreatorPage::Draw()
{
	title.Draw();
}