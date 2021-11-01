#include "StartPage.h"
#include "Settings.h"
#include "UIStartPage.h"

StartPage::StartPage()
{
    if (sf::Shader::isAvailable())
    {
        shaderT.create(Settings::MULTIPLIED_SIZE_SCREEN.x, Settings::MULTIPLIED_SIZE_SCREEN.y);
        shaderS.setTexture(shaderT);
        shaderS.setPosition(-96, -54);

        if (!shader.loadFromFile("Shader/StarWars.frag", sf::Shader::Fragment))
        {
            // erreur...
        }
        else
        {
            shader.setUniform("resolution", sf::Vector2f(Settings::SIZE_SCREEN.x, Settings::SIZE_SCREEN.y));
        }
    }

    UIStartPage* tempUI = new UIStartPage(this);
    ui = tempUI;
}
StartPage::~StartPage()
{
    free(ui);
}


void StartPage::ManageEvent()
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
        else if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }
}

void StartPage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
}
void StartPage::Update()
{
    ManageEvent();

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

    ui->Update();
    ui->Draw(shader);
}