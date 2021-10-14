#include "UIStartPage.h"

UIStartPage::UIStartPage(StartPage* p)
{
	page = p;

	continueButton.SetTexture("Images/UI/ClickToContinue.png");
	continueButton.SetPosition(1630, 1060);
    continueButton.SetScale(0.5f, 0.5f);

    storyText.setFont(SelectedFont::instance->GetFont());
    positionText.x = Settings::WIDTH_SCREEN / 2.0f - 370.0f;
    positionText.y = Settings::HEIGHT_SCREEN;
    storyText.setPosition(positionText);
    storyText.setString(history);
    storyText.setCharacterSize(18);
    storyText.setFillColor(sf::Color::White);
}

UIStartPage::~UIStartPage()
{

}

void UIStartPage::Update(Shader& shader)
{
    animation += Timer::instance->GetDeltaTime();

    positionText.y -= 20.0f * Timer::instance->GetDeltaTime();
    storyText.setPosition(positionText);
    StaticWindow::window->draw(storyText);

    int visibility = (sin(animation) + 1) * 60;

    Color visi(255, 255, 255, visibility);

    

    mousePosition = MouseTool::GetGlobalPosition();
    continueButton.DoesClick(mousePosition);
    continueButton.SetColor(visi);
    continueButton.Draw();
}