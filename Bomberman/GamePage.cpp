#include "GamePage.h"
#include "UIGamePage.h"

GamePage::GamePage()
{
	//player;
    UIGamePage* temp = new UIGamePage(this);
    ui = temp;
}

GamePage::~GamePage()
{
    free(ui);
}

void GamePage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
}

void GamePage::Update()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            StaticWindow::window->close();
    }

    //player.GetDirection();
    //player.Move();
    player.Draw();
}