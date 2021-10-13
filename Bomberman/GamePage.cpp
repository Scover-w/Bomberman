#include "GamePage.h"

GamePage::GamePage()
{
	player;
}

GamePage::~GamePage()
{

}

void GamePage::Update()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            StaticWindow::window->close();
    }

    player.GetDirection();
    player.Move();
    player.Draw();
	
}