#include "GamePage.h"
#include "UIGamePage.h"

GamePage::GamePage()
{
    player.SetMap(map);
    UIGamePage* temp = new UIGamePage(this);
    ui = temp;
    hasWin = false;
}

GamePage::~GamePage()
{
    free(ui);
}

void GamePage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
    MapEditor::LoadRandomMap(map);
    MapDrawer::instance->SetMap(map, false);
    player.ResetPosition();
    MapDrawer::instance->SetPlayer(&player);
}

void GamePage::Update()
{
    ui->Update();

    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }

    player.GetDirection();
    player.Move();

    MapDrawer::instance->DrawEnv(true);
    MapDrawer::instance->Draw();
    MapDrawer::instance->DrawEnv(false);

}