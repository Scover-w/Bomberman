#include "GamePage.h"
#include "UIGamePage.h"

GamePage::GamePage()
{
    player.SetMap(map);
    UIGamePage* temp = new UIGamePage(this);
    ui = temp;
    hasWin = false;

    for (int i = 0; i < 169; i++)
    {
        mapExplosion[i] = -1.0f;
        mapBomb[i] = -1.0f;
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
    player.Reset();
    MapDrawer::instance->SetPlayer(&player);
}

void GamePage::Update()
{
    ui->Update();

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
            map[posPlayerIndex] = MapEntity::BombT;
            bombPlayerId.push(player.GetId());
            positionBombs.push(posPlayerIndex);
        }
        
    }

    UpdateBombs();
    UpdateExplosions();
    player.Update();


    MapDrawer::instance->DrawEnv(true);
    MapDrawer::instance->Draw();
    MapDrawer::instance->DrawEnv(false);

    ui->Draw();

}

void GamePage::UpdateBombs()
{
    float value;
    float deltaTime = Timer::instance->GetDeltaTime();
    for (int i = 0; i < 169; i++)
    {
        value = mapBomb[i];

        if (value < 0.0f)
            continue;

        value += deltaTime;

        if (value > 3.0f)
        {
            value = -1.0f;
            int positionBombId = positionBombs.front();
            positionBombs.pop();
            ExplosionData tempExplositionE = eCalcul.GetData(map, mapExplosion, positionBombId, player.GetRange());
            player.CheckDamageBomb(tempExplositionE);

            int frontValue = bombPlayerId.front();
            bombPlayerId.pop();
            if (frontValue == player.GetId())
                player.AddBomb();
            
        }

        mapBomb[i] = value;
    }
}

void GamePage::UpdateExplosions()
{
    float value;
    float deltaTime = Timer::instance->GetDeltaTime();
    for (int i = 0; i < 169; i++)
    {
        value = mapExplosion[i];

        if (value < 0.0f)
            continue;

        value += deltaTime;

        if (value > 1.0f)
            value = -1.0f;


        mapExplosion[i] = value;
    }
}