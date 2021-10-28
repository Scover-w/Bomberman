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
                             "PinkRuby", "RedPeridot", "RedRuby",
                             "WhitePeridot", "YellowPeridot"};
                                

    string nameWall[] = { "BrickAlt1", "Bricks1", "BrownBrick", 
                          "GreyBrick", };


    string nameGround[] = { "autumn",  "brightWood",  "darkWood",
                          "gold",  "grass",  "hell",
                          "lapis", "magma", "obsidian",
                          "sand", "snow", "spongeCakeChocolate",
                          "spongeCakePink", "stone", "swamp", 
                          "yellowGrass"};

    for (int i = 0; i < 14; i++)
    {
        destructables[i].SetTexture("Images/Destructible/" + nameDestruc[i] + ".png");
        destructables[i].SetOrigin(80, 37);
    }

    for (int i = 0; i < 4; i++)
    {
        walls[i].SetTexture("Images/Walls/" + nameWall[i] + ".png");
        walls[i].SetOrigin(80, 37);
    }

    for (int i = 0; i < 16; i++)
    {
        grounds[i].SetTexture("Images/Grounds/" + nameGround[i] + ".png");
        grounds[i].SetOrigin(80, 0);
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

    shadowItem.SetTexture("Images/Collectables/Shadow.png");
    shadowItem.SetOrigin(15.0f, -6.0f);

    transparency = Color(255, 255, 255, 100);
}

MapDrawer::~MapDrawer()
{

}

void MapDrawer::SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169])
{
	map = map2;
    mapExplosion = mapE;
    mapBomb = mapB;
    selectedWall = CustomRandom::GetRandom(0, 4);
    selectedDestructable = CustomRandom::GetRandom(0, 14);
    selectedGround = CustomRandom::GetRandom(0, 16);
}

void MapDrawer::SetMap(MapEntity(&map2)[169])
{
    map = map2;
    selectedWall = 0;
    selectedDestructable = 0;
    selectedGround = 0;
}

void MapDrawer::SetPlayers(Player* p, BotPlayer* b1, BotPlayer* b2, BotPlayer* b3)
{
    player = p;
    bot1 = b1;
    bot2 = b2;
    bot3 = b3;
}

void MapDrawer::DrawWallEnv(int i)
{
    Vector2f pos = CustomMath::UM_PositionToIsoCoordF(i);
    wallEnvImg.SetPosition(pos);
    wallEnvImg.Draw();
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

void MapDrawer::Draw()
{

    Vector2f positionSelection;

    for (int i = 0; i < 169; i++)
    {
        int entity = *(map + i);
        if (!(entity == MapEntity::Wall || entity == MapEntity::DBlock))
        {
            positionSelection = CustomMath::GM_PositionToIsoCoordF(i);
            grounds[selectedGround].SetPosition(positionSelection);
            grounds[selectedGround].Draw();
        }
    }

    time = Timer::instance->GetTimeSpent();

	for (int i = 0; i < 169; i++)
	{
        positionSelection = CustomMath::GM_PositionToIsoCoordF(i);

 
        switch (*(map + i))
        {

            case MapEntity::Wall:
                walls[selectedWall].SetPosition(positionSelection);
                walls[selectedWall].Draw();
                break;

            case MapEntity::DBlock:
                destructables[selectedDestructable].SetPosition(positionSelection);
                destructables[selectedDestructable].Draw();
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

void MapDrawer::DrawEditor()
{
    Vector2f positionSelection;

    for (int i = 0; i < 169; i++)
    {
        positionSelection = CustomMath::GM_PositionToIsoCoordF(i);


        switch (*(map + i))
        {
            case MapEntity::None:
                grounds[selectedGround].SetPosition(positionSelection);
                grounds[selectedGround].Draw();
                break;
            case MapEntity::Wall:
                walls[selectedWall].SetPosition(positionSelection);
                walls[selectedWall].Draw();
                break;

            case MapEntity::DBlock:
                destructables[selectedDestructable].SetPosition(positionSelection);
                destructables[selectedDestructable].Draw();
                break;
        }
    }
}

float MapDrawer::GetDeltaAnimItem(int x)
{
    return (sin(x + time) + 1) * -5.0f;
}

void MapDrawer::DrawShadowItem(Vector2f& p, float x)
{
    transparency.a = ((sin(-x + time) + 1) * 0.5f * 0.4f + 0.3f) * 255.0f;
    shadowItem.SetColor(transparency);
    shadowItem.SetPosition(p);
    shadowItem.Draw();
}