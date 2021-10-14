#include "MenuPage.h"
#include "Settings.h"

MenuPage::MenuPage()
{
    if (sf::Shader::isAvailable())
    {
        shaderT.create(Settings::MULTIPLIED_WIDTH_SCREEN, Settings::MULTIPLIED_HEIGHT_SCREEN);
        shaderS.setTexture(shaderT);
        shaderS.setPosition(-96, -54);
        if (!shader.loadFromFile("Shader/turnWhite.frag", sf::Shader::Fragment))
        {
            // erreur...
        }
        else
        {
            shader.setUniform("resolution", sf::Vector2f(Settings::WIDTH_SCREEN, Settings::HEIGHT_SCREEN));
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
        if (event.type == event.KeyPressed && event.key.code == Keyboard::Space)
        {
            Page page = Page::Game;
            DataManager::instance->SetCurrentPage(page);
        }
        else if (event.type == event.KeyPressed && event.key.code == Keyboard::C)
        {
            Page page = Page::LevelCreator;
            DataManager::instance->SetCurrentPage(page);
        }
        else if (event.type == Event::Closed)
            StaticWindow::window->close();
        
    }

    shader.setUniform("time", clk.getElapsedTime().asSeconds());

    if (sf::Shader::isAvailable())
    {
        StaticWindow::window->draw(shaderS, &shader);
    }
}