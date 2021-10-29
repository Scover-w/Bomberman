#include "EndPage.h"
#include "UIEndPage.h"
#include "MapDrawer.h"

EndPage::EndPage()
{
	UIEndPage* temp = new UIEndPage(this);
	ui = temp;
}

EndPage::~EndPage()
{
	free(ui);
}

void EndPage::LoadPage()
{
	DataManager::instance->NoFirstLoad();

	hasWin = DataManager::instance->AskWin();
	ui->SetWin(hasWin);
}

void EndPage::ManageEvent()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }
}

void EndPage::Update()
{
	ui->Update();

	ManageEvent();

	MapDrawer::instance->DrawEnv(true);
	MapDrawer::instance->DrawArenaInWall();
	MapDrawer::instance->DrawEnv(false);

	ui->Draw();
}

void EndPage::MenuClick()
{
	Page page = Page::Menu;
	DataManager::instance->SetCurrentPage(page);
}

void EndPage::RestartClick()
{
	Page page = Page::Game;
	DataManager::instance->SetCurrentPage(page);
}