#include "GamePage.h"
#include "UIGamePage.h"
#include "SoundManager.h"

GamePage::GamePage()
{
    player.SetMap(map);
    UIGamePage* temp = new UIGamePage(this);
    ui = temp;

    ui->SetPlayers(&player, &bot1, &bot2, &bot3);

    hasWin = false;

    explosionCalcul.SetMaps(map, mapExplosion, mapBomb);
    MapDrawer::instance->SetPlayers(&player, &bot1, &bot2, &bot3);
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
    
    player.Reset();
    bot1.Reset();
    bot2.Reset();
    bot3.Reset();
    

    for (int i = 0; i < 169; i++)
    {
        mapExplosion[i] = -1.0f;
        mapBomb[i] = -1.0f;
        bombOwner[i] = -1;
    }
}

void GamePage::PoseBomb(int posId, int playerId)
{
    mapBomb[posId] = 0.0f;
    map[posId] = MapEntity::Bomb;
    bombOwner[posId] = playerId;

    switch (playerId)
    {
        case 0:
            player.SetOnBombId(posId);
            break;
        case 1:
            bot1.SetOnBombId(posId);
            break;
        case 2:
            bot2.SetOnBombId(posId);
            break;
        case 3:
            bot3.SetOnBombId(posId);
            break;
    }
    
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
            PoseBomb(posPlayerIndex, player.GetId());
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

    int posId;
    
    posId = bot1.Update();
    if (posId != -1)
    {
        PoseBomb(posId, bot1.GetId());
    }

    posId = bot2.Update();
    if (posId != -1)
    {
        PoseBomb(posId, bot2.GetId());
    }

    posId = bot3.Update();
    if (posId != -1)
    {
        PoseBomb(posId, bot3.GetId());
    }


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
            SoundManager::instance->Play(SoundType::Explosion);
            value = -1.0f;
            int ownerId = bombOwner[i];
            ExplosionData tempExplositionE = explosionCalcul.GetData(i, player.GetRange());
            player.CheckDamageBomb(tempExplositionE);

            if (ownerId == player.GetId())
            {
                bot1.CheckDamageBomb(tempExplositionE);
                bot2.CheckDamageBomb(tempExplositionE);
                bot3.CheckDamageBomb(tempExplositionE);
            }
            
            bombOwner[i] = -1;
            map[i] = MapEntity::None;

            if (ownerId == player.GetId())
            {
                player.AddBomb();
                player.ResetOnBombId(i);
            }
            else if (ownerId == bot1.GetId())
            {
                bot1.AddBomb();
                bot1.ResetOnBombId(i);
            }
            else if (ownerId == bot2.GetId())
            {
                bot2.AddBomb();
                bot2.ResetOnBombId(i);
            }
            else if (ownerId == bot3.GetId())
            {
                bot3.AddBomb();
                bot3.ResetOnBombId(i);
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
        SoundManager::instance->Play(SoundType::Lose);
        Page page = Page::End;
        DataManager::instance->SetWinValue(false);
        DataManager::instance->SetCurrentPage(page);
        return;
    }

    if (bot1.IsDead() && bot2.IsDead() && bot3.IsDead())
    {
        SoundManager::instance->Play(SoundType::Win);
        Page page = Page::End;
        DataManager::instance->SetWinValue(true);
        DataManager::instance->SetCurrentPage(page);
        return;
    }
}