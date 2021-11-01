#include "MapDrawer.h"

MapDrawer* MapDrawer::instance;

MapDrawer::MapDrawer()
{
	instance = this;

    wallEnvImg.SetTexture("Images/Walls/BlackBrick.png");
    wallEnvImg.SetOrigin(80, 0); // 37 base

    string nameDestruc[] = { "BlackPeridot",  "BluePeridot",  "BlueRuby",
                             "GreenPeridot",  "GreenRuby",  "OrangePeridot",
                             "OrangeRuby", "PinkPeridot", "YellowRuby",
                             "RedPeridot", "RedRuby",
                             "WhitePeridot", "YellowPeridot"};
                                

    string nameWall[] = { "BrickAlt1", "Bricks1", "BrownBrick", 
                          "GreyBrick", };


    string nameGround[] = { "autumn",  "brightWood",  "darkWood",
                          "grass", "magma", "obsidian",
                          "sand", "spongeCakeChocolate",
                          "stone", "swamp"};

    for (int i = 0; i < 13; i++)
    {
        destructableImgs[i].SetTexture("Images/Destructible/" + nameDestruc[i] + ".png");
        destructableImgs[i].SetOrigin(80, 37);
    }

    for (int i = 0; i < 4; i++)
    {
        wallImgs[i].SetTexture("Images/Walls/" + nameWall[i] + ".png");
        wallImgs[i].SetOrigin(80, 37);
    }

    for (int i = 0; i < 10; i++)
    {
        groundImgs[i].SetTexture("Images/Grounds/" + nameGround[i] + ".png");
        groundImgs[i].SetOrigin(80, 0);
    }

    bombImg.SetTexture("Images/Collectables/Bomb.png");
    bombImg.SetOrigin(120, 68);

    explosionImg.SetTexture("Images/Bomb/Explosion.png");
    explosionImg.SetOrigin(125, 150);
    explosionImg.SetScale(0.5f, 0.5f);
    explosionMaskSprite.height = 250;
    explosionMaskSprite.width = 250;

    heartImg.SetTexture("Images/Collectables/heart.png");
    heartImg.SetOrigin(123, 30 + 50.0f);
    heartImg.SetScale(0.15f, 0.15f);

    speedImg.SetTexture("Images/Collectables/LightSpeed.png");
    speedImg.SetOrigin(316, 70 + 50.0f);
    speedImg.SetScale(0.05f, 0.05f);

    bombImg2.SetTexture("Images/Collectables/Bomb.png");
    bombImg2.SetOrigin(120, 63 + 50.0f);
    bombImg2.SetScale(0.15f, 0.15f);

    powerImg.SetTexture("Images/Collectables/Boom.png");
    powerImg.SetOrigin(60, 0 + 50.0f);
    powerImg.SetScale(0.20f, 0.20f);

    shadowItemImg.SetTexture("Images/Collectables/Shadow.png");

    transparency = Color(255, 255, 255, 100);
}
MapDrawer::~MapDrawer()
{

}

#pragma region Private
float MapDrawer::GetDeltaAnimItem(int x)
{
    return (sin(x + time) + 1) * -5.0f;
}

void MapDrawer::DrawShadowItem(Vector2f& p, float x)
{
    transparency.a = ((sin(-x + time) + 1) * 0.5f * 0.4f + 0.3f) * 255.0f;
    shadowItemImg.SetColor(transparency);
    shadowItemImg.SetPosition(p);
    shadowItemImg.Draw();
}
void MapDrawer::DrawWallEnv(int i)
{
    Vector2f pos = CustomMath::UM_PositionToIsoCoordF(i);
    wallEnvImg.SetPosition(pos);
    wallEnvImg.Draw();
}
void MapDrawer::DrawGround(int i)
{
    Vector2f positionSelection = CustomMath::GM_PositionToIsoCoordF(i);
    groundImgs[selectedGround].SetPosition(positionSelection);
    groundImgs[selectedGround].Draw();
}
#pragma endregion


#pragma region Public
void MapDrawer::SetMap(MapEntity(&map2)[169])
{
    map = map2;
    selectedWall = 0;
    selectedDestructable = 0;
    selectedGround = 0;
}
void MapDrawer::SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169])
{
    map = map2;
    mapExplosion = mapE;
    mapBomb = mapB;
    selectedWall = CustomRandom::GetRandom(0, 4);
    selectedDestructable = CustomRandom::GetRandom(0, 13);
    selectedGround = CustomRandom::GetRandom(0, 10);
}
void MapDrawer::SetPlayers(Player* p, BotPlayer* b1, BotPlayer* b2, BotPlayer* b3)
{
    player = p;
    bot1 = b1;
    bot2 = b2;
    bot3 = b3;
}

void MapDrawer::DrawEnv(bool isFirstPart)
{
    if (isFirstPart)
    {
        // Right Up Side
        for (int i = 13, j = 3; i < 203; i += 27)
        {
            for (int k = 0; k < j; k++)
            {
                DrawWallEnv(i + k);
            }
            j += 2;
        }

        // Left Up Side
        int i = 229;
        int j = 3;
        for (; i < 365; i += 27)
        {
            for (int k = 0; k < j; k++)
            {
                DrawWallEnv(i + k);
            }
            j++;
        }
        for (; i < 567; i += 29)
        {
            for (int k = 0; k < j; k++)
            {
                DrawWallEnv(i + k);
            }
            j--;
        }
    }
    else
    {
        // Right side
        for (int i = 245, j = 3; i < 582; i += 28)
        {
            for (int k = 0; k < j; k++)
            {
                if ((i + k) % 28 == 0)
                    break;
                else
                    DrawWallEnv(i + k);
            }

            j += (i < 386) ? 1 : -1;
        }

        // Left side
        for (int i = 594, j = 17; i < 798; i += 29)
        {
            for (int k = 0; k < j; k++)
            {
                DrawWallEnv(i + k);
            }
            j -= 2;
        }


    }

}
void MapDrawer::DrawArenaInWall()
{
    for (int i = 232; i < 570; i += Settings::SIZE_UI_MAP)
    {
        for (int j = 0; j < 13; j++)
        {
            DrawWallEnv(i + j);
        }
    }
}
void MapDrawer::DrawAnimatedArenaInWall(const float& timer)
{
    Vector2f pos;
    Vector2f delta;
    float translation = -Settings::MULTIPLIED_SIZE_SCREEN.y;
    float step = 0.003f;
    int k = 0;
    float state = timer / 1.5f;
    float relativeState;

    for (int i = 232; i < 570; i += Settings::SIZE_UI_MAP)
    {
        for (int j = 0; j < 13; j++)
        {
            relativeState = timer - (k * step);
            if (relativeState < 0)
                delta = Vector2f(0, 0);
            else
                delta = Vector2f(0, translation * relativeState);

            pos = CustomMath::UM_PositionToIsoCoordF(i + j);
            wallEnvImg.SetPosition(pos + delta);
            wallEnvImg.Draw();

        }
        k += 13;
    }
}
void MapDrawer::DrawArenaInGround()
{
    Vector2f positionSelection;

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            DrawGround(i * 13 + j);
        }
    }
}
void MapDrawer::DrawEditor()
{
    Vector2f positionSelection;

    for (int i = 0; i < 169; i++)
    {
        positionSelection = CustomMath::GM_PositionToIsoCoordF(i);


        switch (*(map + i))
        {
        case MapEntity::None:
            groundImgs[selectedGround].SetPosition(positionSelection);
            groundImgs[selectedGround].Draw();
            break;
        case MapEntity::Wall:
            wallImgs[selectedWall].SetPosition(positionSelection);
            wallImgs[selectedWall].Draw();
            break;

        case MapEntity::DBlock:
            destructableImgs[selectedDestructable].SetPosition(positionSelection);
            destructableImgs[selectedDestructable].Draw();
            break;
        }
    }
}
void MapDrawer::Draw()
{

    Vector2f positionSelection;

    for (int i = 0; i < 169; i++)
    {
        int entity = *(map + i);
        if (!(entity == MapEntity::Wall || entity == MapEntity::DBlock))
        {
            DrawGround(i);
        }
    }

    time = Timer::instance->GetTimeSpent();

    for (int i = 0; i < 169; i++)
    {
        positionSelection = CustomMath::GM_PositionToIsoCoordF(i);


        switch (*(map + i))
        {

        case MapEntity::Wall:
            wallImgs[selectedWall].SetPosition(positionSelection);
            wallImgs[selectedWall].Draw();
            break;

        case MapEntity::DBlock:
            destructableImgs[selectedDestructable].SetPosition(positionSelection);
            destructableImgs[selectedDestructable].Draw();
            break;
        }

        if (player->GetPositionIndex() == i)
        {
            player->Draw();
        }

        if (bot1->GetPositionIndex() == i)
        {
            bot1->Draw();
        }

        if (bot2->GetPositionIndex() == i)
        {
            bot2->Draw();
        }

        if (bot3->GetPositionIndex() == i)
        {
            bot3->Draw();
        }

        if (*(mapBomb + i) >= 0.0f)
        {
            bombImg.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapBomb + i)) + 1) * -5.0f);
            bombImg.SetScale(.3f + sin(*(mapBomb + i) * 2.0f) * 0.01f, .3f + sin(*(mapBomb + i) * 2.0f) * 0.01f);
            bombImg.Draw();
        }

        if (*(map + i) > MapEntity::Bomb)
        {
            float x = CustomRandom::GetPseudoRandom(i);
            switch (*(map + i))
            {
            case MapEntity::LifeIt:
                DrawShadowItem(positionSelection, x);
                heartImg.SetPosition(positionSelection.x, positionSelection.y + GetDeltaAnimItem(x));
                heartImg.Draw();
                break;
            case MapEntity::BombIt:
                DrawShadowItem(positionSelection, x);
                bombImg2.SetPosition(positionSelection.x, positionSelection.y + GetDeltaAnimItem(x));
                bombImg2.Draw();
                break;
            case MapEntity::SpeedIt:
                DrawShadowItem(positionSelection, x);
                speedImg.SetPosition(positionSelection.x, positionSelection.y + GetDeltaAnimItem(x));
                speedImg.Draw();
                break;
            default: // PowerIt
                DrawShadowItem(positionSelection, x);
                powerImg.SetPosition(positionSelection.x, positionSelection.y + GetDeltaAnimItem(x));
                powerImg.Draw();
                break;
            }
        }



        if (*(mapExplosion + i) >= 0.0f)
        {
            int state = *(mapExplosion + i) / 0.04166666666667f;
            explosionMaskSprite.top = 250 * ((int)(state / 4));
            explosionMaskSprite.left = 250 * (state % 4);
            explosionImg.SetTextureRect(explosionMaskSprite);
            explosionImg.SetPosition(positionSelection);
            explosionImg.Draw();
        }
    }
}
#pragma endregion




