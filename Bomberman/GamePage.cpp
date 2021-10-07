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
        cout << event.type << endl;
        if (event.type == event.KeyPressed || event.type == event.KeyReleased)
        {
            player.KeyManager(event);
        }
        else if (event.type == Event::Closed)
            StaticWindow::window->close();
    }

    player.GetDirection();
    player.Move();
    player.Draw();
	
}