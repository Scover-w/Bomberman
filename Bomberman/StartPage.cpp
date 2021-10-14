#include "StartPage.h"
#include "Settings.h"
#include "UIStartPage.h"

StartPage::StartPage()
{
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

    UIStartPage* tempUI = new UIStartPage(this);
    ui = tempUI;
}

StartPage::~StartPage()
{
    free(ui);
}

void StartPage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
}

void StartPage::Update()
{
    Event event;

    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == event.KeyPressed || event.type == event.MouseButtonPressed)
        {
            CursorManager::instance->SetNormalCursor();
            Page page = Page::Menu;
            DataManager::instance->SetCurrentPage(page);
        }
        else if (event.type == Event::Closed)
            StaticWindow::window->close();
    }

    animation += Timer::instance->GetDeltaTime();

    if (animation >= 65.0f)
    {
        Page page = Page::Menu;
        DataManager::instance->SetCurrentPage(page);
    }

    shader.setUniform("time", animation);

    if (sf::Shader::isAvailable())
    {
        StaticWindow::window->draw(shaderS, &shader);
    }

    ui->Update(shader);
}