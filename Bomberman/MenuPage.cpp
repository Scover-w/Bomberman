#include "MenuPage.h"
#include "Settings.h"
#include "UIMenuPage.h"

MenuPage::MenuPage()
{
    UIMenuPage* temp = new UIMenuPage(this);
    ui = temp;
}

MenuPage::~MenuPage()
{
    free(ui);
}

void MenuPage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
    timerAnimation = 1.5f;
    inAnimation = true;
    directionAnimation = false;
    ui->HideButtons();
}

void MenuPage::ManageEvent()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::C))
        {
            Page page = Page::LevelCreator;
            DataManager::instance->SetCurrentPage(page);
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::E))
        {
            Page page = Page::End;
            DataManager::instance->SetCurrentPage(page);
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::T))
        {
            inAnimation = true;
            timerAnimation = 0.0f;
            directionAnimation = true;
        }
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }
}

void MenuPage::ManageMap()
{
    MapDrawer::instance->DrawEnv(true);

    if (inAnimation)
    {
        timerAnimation = (directionAnimation) ? timerAnimation + Timer::instance->GetDeltaTime() : timerAnimation - Timer::instance->GetDeltaTime();
        MapDrawer::instance->DrawArenaInGround();
        MapDrawer::instance->DrawAnimatedArenaInWall(timerAnimation);
    }
    else
    {
        MapDrawer::instance->DrawArenaInWall();
    }

    if (inAnimation)
    {
        if (timerAnimation > 1.5f)
        {
            DataManager::instance->SetCurrentPage(wishPage);
        }
        else if (timerAnimation <= 0.0f)
        {
            inAnimation = false;
            ui->DisplayButtons();
        }
    }
    

    MapDrawer::instance->DrawEnv(false);
}

void MenuPage::Update()
{
    ui->Update();

    ManageEvent();
    ManageMap();

    ui->Draw();
}

void MenuPage::PlayClick()
{
    inAnimation = true;
    timerAnimation = 0.0f;
    directionAnimation = true;
    wishPage = Page::Game;
    ui->HideButtons();
}

void MenuPage::EditorClick()
{
    inAnimation = true;
    timerAnimation = 0.0f;
    directionAnimation = true;
    wishPage = Page::LevelCreator;
    ui->HideButtons();
}