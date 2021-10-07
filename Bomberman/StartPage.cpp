#include "StartPage.h"
#include "Settings.h"


StartPage::StartPage()
{
    if (!font.loadFromFile("Font/Chakra_Petch/ChakraPetch-Regular.ttf")) // Quicksand/Quicksand-VariableFont_wght.ttf
    {
        // error...
    }

    storyText.setFont(font);
    positionText.x = Settings::WIDTH_SCREEN / 2.0f - 370.0f;
    positionText.y = Settings::HEIGHT_SCREEN;
    storyText.setPosition(positionText);
    storyText.setString(history);
    storyText.setCharacterSize(18);
    storyText.setFillColor(sf::Color::White);

    if (sf::Shader::isAvailable())
    {
        shaderT.create(Settings::MULTIPLIED_WIDTH_SCREEN, Settings::MULTIPLIED_HEIGHT_SCREEN);
        shaderS.setTexture(shaderT);
        shaderS.setPosition(-96, -54);
        // https://www.glslsandbox.com
        if (!shader.loadFromFile("Shader/shadertest.frag", sf::Shader::Fragment))
        {
            // erreur...
        }
        else
        {
            shader.setUniform("resolution", sf::Vector2f(Settings::WIDTH_SCREEN, Settings::HEIGHT_SCREEN));
        }
    }
}

StartPage::~StartPage()
{

}

void StartPage::Update()
{
    Event event;

    timeSpent += Timer::instance->GetDeltaTime();

    if (timeSpent >= 65.0f)
    {
        Page page = Page::Menu;
        DataManager::dataManager->SetCurrentPage(page);
    }

    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == event.KeyPressed)
        {
            Page page = Page::Menu;
            DataManager::dataManager->SetCurrentPage(page);
        }
        else if (event.type == Event::Closed)
            StaticWindow::window->close();
    }

    DrawText();
}


void StartPage::DrawText()
{
    shader.setUniform("time", clk.getElapsedTime().asSeconds());
    positionText.y -= 20.0f * Timer::instance->GetDeltaTime();
    storyText.setPosition(positionText);


    if (sf::Shader::isAvailable())
    {
        StaticWindow::window->draw(shaderS, &shader);
    }

    StaticWindow::window->draw(storyText);

    
    
}