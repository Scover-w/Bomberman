#include "GamePage.h"
#include "UIGamePage.h"

GamePage::GamePage()
{
    player.SetMap(map);
    /*bot1.SetMap(map);
    bot2.SetMap(map);
    bot3.SetMap(map);*/
    UIGamePage* temp = new UIGamePage(this);
    ui = temp;
    hasWin = false;

    for (int i = 0; i < 169; i++)
    {
        mapExplosion[i] = -1.0f;
        mapBomb[i] = -1.0f;
        bombOwner[i] = -1;
    }
}

GamePage::~GamePage()
{
    free(ui);
}

void GamePage::LoadPage()
{
    DataManager::instance->NoFirstLoad();
    MapEditor::LoadRandomMap(map);
    MapDrawer::instance->SetMaps(map, mapExplosion, mapBomb);
    explosionCalcul.SetMaps(map, mapExplosion, mapBomb);
    player.Reset();
    bot1.Reset();
    bot2.Reset();
    bot3.Reset();
    MapDrawer::instance->SetPlayers(&player, &bot1, &bot2, &bot3);
}

void GamePage::ManageEvent()
{
    // Rising front
    beforeSpace = currentSpace;
    currentSpace = Keyboard::isKeyPressed(Keyboard::Space);

    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }


    if (currentSpace && !beforeSpace && player.AskRemoveBomb())
    {
        int posPlayerIndex = player.GetPositionIndex();
        if (mapBomb[posPlayerIndex] > 0.0f)
        {
            player.AddBomb();
        }
        else
        {
            mapBomb[posPlayerIndex] = 0.0f;
            map[posPlayerIndex] = MapEntity::Bomb;
            bombOwner[posPlayerIndex] = player.GetId();
            player.SetOnBombId(posPlayerIndex);
        }
    }
}

void GamePage::Update()
{
    ui->Update();

    ManageEvent();

    float deltaT = Timer::instance->GetDeltaTime();

    UpdateBombs(deltaT);
    UpdateExplosions(deltaT);
    player.Update();
    bot1.Update();
    bot2.Update();
    bot3.Update();


    MapDrawer::instance->DrawEnv(true);
    MapDrawer::instance->Draw();
    MapDrawer::instance->DrawEnv(false);

    

    ui->Draw();

    CheckEndGame();
}

void GamePage::UpdateBombs(float deltaTime)
{
    float value;
    for (int i = 0; i < 169; i++)
    {
        value = mapBomb[i];

        if (value < 0.0f)
            continue;

        value += deltaTime;

        if (value > 3.0f)
        {
            value = -1.0f;

            ExplosionData tempExplositionE = explosionCalcul.GetData(i, player.GetRange());
            player.CheckDamageBomb(tempExplositionE);

            int frontValue = bombOwner[i];
            bombOwner[i] = -1;
            map[i] = MapEntity::None;
            if (frontValue == player.GetId())
            {
                player.AddBomb();
                player.ResetOnBombId(i);
            }
            
        }

        mapBomb[i] = value;
    }
}

void GamePage::UpdateExplosions(float deltaTime)
{
    float value;
    for (int i = 0; i < 169; i++)
    {
        value = mapExplosion[i];

        if (value < 0.0f)
            continue;

        value += deltaTime;

        if (value > 0.5f)
            value = -1.0f;

        mapExplosion[i] = value;
    }
}


void GamePage::CheckEndGame()
{
    if (player.IsDead())
    {
        Page page = Page::End;
        DataManager::instance->SetWinValue(false);
        DataManager::instance->SetCurrentPage(page);
        return;
    }

    if (bot1.IsDead() && bot2.IsDead() && bot3.IsDead())
    {
        Page page = Page::End;
        DataManager::instance->SetWinValue(true);
        DataManager::instance->SetCurrentPage(page);
        return;
    }
}