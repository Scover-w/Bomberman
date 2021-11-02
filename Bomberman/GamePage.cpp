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

#pragma region Private
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

            ExplosionData tempExplositionE;

            switch (ownerId)
            {
                case 0:
                    tempExplositionE = explosionCalcul.GetData(i, player.GetRange());
                    player.PutPackBomb();
                    player.ResetOnBombId(i);

                    bot1.CheckDamageBomb(tempExplositionE);
                    bot2.CheckDamageBomb(tempExplositionE);
                    bot3.CheckDamageBomb(tempExplositionE);
                    break;
                case 1: 
                    tempExplositionE = explosionCalcul.GetData(i, bot1.GetRange());
                    bot1.PutPackBomb();
                    bot1.ResetOnBombId(i);
                    break;
                case 2: 
                    tempExplositionE = explosionCalcul.GetData(i, bot2.GetRange());
                    bot2.PutPackBomb();
                    bot2.ResetOnBombId(i);
                    break;
                case 3: 
                    tempExplositionE = explosionCalcul.GetData(i, bot3.GetRange());
                    bot3.PutPackBomb();
                    bot3.ResetOnBombId(i);
                    break;
            }

            player.CheckDamageBomb(tempExplositionE);

            bombOwner[i] = -1;
            map[i] = MapEntity::None;
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
void GamePage::PoseBomb(int posId, int playerId)
{
    mapBomb[posId] = 0.0f;
    map[posId] = MapEntity::Bomb;
    bombOwner[posId] = playerId;


    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0:
                if(player.GetPositionIndex() == posId)
                    player.SetOnBombId(posId);
                break;
            case 1:
                if (bot1.GetPositionIndex() == posId)
                    bot1.SetOnBombId(posId);
                break;
            case 2:
                if (bot2.GetPositionIndex() == posId)
                    bot2.SetOnBombId(posId);
                break;
            case 3:
                if (bot3.GetPositionIndex() == posId)
                    bot3.SetOnBombId(posId);
                break;
        }
    }
}
#pragma endregion


#pragma region Public
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
#pragma endregion

