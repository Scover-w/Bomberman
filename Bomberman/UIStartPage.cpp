#include "UIStartPage.h"

UIStartPage::UIStartPage(StartPage* p)
{
	page = p;

    continueBtn.SetTexture("Images/UI/StartPage/ClickToContinue.png");
    continueBtn.SetPosition(1630, 1060);
    continueBtn.SetScale(0.5f, 0.5f);

    storyTxt.setFont(SelectedFont::instance->GetFont());
    positionTextV2f.x = Settings::SIZE_SCREEN.x / 2.0f - 370.0f;
    positionTextV2f.y = Settings::SIZE_SCREEN.y;
    storyTxt.setPosition(positionTextV2f);
    storyTxt.setString(history);
    storyTxt.setCharacterSize(18);
    storyTxt.setFillColor(sf::Color::White);
}
UIStartPage::~UIStartPage()
{

}


void UIStartPage::Update()
{
    animation += Timer::instance->GetDeltaTime();

    positionTextV2f.y -= 20.0f * Timer::instance->GetDeltaTime();
    storyTxt.setPosition(positionTextV2f);
    
    int visibility = (sin(animation) + 1) * 60;

    Color visi(255, 255, 255, visibility);

    mousePositionV2f = MouseTool::GetGlobalPosition();
    continueBtn.DoesClick(mousePositionV2f);
    continueBtn.SetColor(visi);
}
void UIStartPage::Draw(Shader& shader)
{
    StaticWindow::window->draw(storyTxt);
    continueBtn.Draw();
}