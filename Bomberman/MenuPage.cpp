#include "MenuPage.h"
#include "Settings.h"

MenuPage::MenuPage()
{
    if (sf::Shader::isAvailable())
    {
        shaderT.create(Settings::MULTIPLIED_SIZE_SCREEN.x, Settings::MULTIPLIED_SIZE_SCREEN.y);
        shaderS.setTexture(shaderT);
        shaderS.setPosition(-96, -54);
        if (!shader.loadFromFile("Shader/WhiteRotation.frag", sf::Shader::Fragment))
        {
            // erreur...
        }
        else
        {
            shader.setUniform("resolution", sf::Vector2f(Settings::SIZE_SCREEN.x, Settings::SIZE_SCREEN.y));
        }
    }
}

MenuPage::~MenuPage()
{

}

void MenuPage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
}

void MenuPage::Update()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == event.KeyPressed && event.key.code == Keyboard::Enter)
        {
            Page page = Page::Game;
            DataManager::instance->SetCurrentPage(page);
        }
        else if (event.type == event.KeyPressed && event.key.code == Keyboard::C)
        {
            Page page = Page::LevelCreator;
            DataManager::instance->SetCurrentPage(page);
        }
        else if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
        
    }

    shader.setUniform("time", clk.getElapsedTime().asSeconds());

    if (sf::Shader::isAvailable())
    {
        StaticWindow::window->draw(shaderS, &shader);
    }
}