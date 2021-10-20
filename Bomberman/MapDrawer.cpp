#include "MapDrawer.h"

MapDrawer* MapDrawer::instance;

MapDrawer::MapDrawer()
{
	instance = this;

    wallEnvImg.SetTexture("Images/Walls/BlackBrick.png");
    wallEnvImg.SetOrigin(80, 37);

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
    heartImg.SetOrigin(123, 30);
    heartImg.SetScale(0.15f, 0.15f);

    speedImg.SetTexture("Images/Collectables/LightSpeed.png");
    speedImg.SetOrigin(316, 70);
    speedImg.SetScale(0.05f, 0.05f);

    bombImg2.SetTexture("Images/Collectables/Bomb.png");
    bombImg2.SetOrigin(120, 63);
    bombImg2.SetScale(0.15f, 0.15f);

    powerImg.SetTexture("Images/Collectables/Boom.png");
    powerImg.SetOrigin(60, 0);
    powerImg.SetScale(0.20f, 0.20f);
}

MapDrawer::~MapDrawer()
{

}

void MapDrawer::SetMaps(MapEntity(&map2)[169], float(&mapE)[169], float(&mapB)[169], float* timeAnim)
{
	map = map2;
    mapExplosion = mapE;
    mapBomb = mapB;
    collectableTime = timeAnim;
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

void MapDrawer::SetPlayer(Player* play)
{
    player = play;
}

void MapDrawer::DrawEnv(bool isFirstPart)
{
    if (isFirstPart)
    {
        // Mirror up
        int indexs[] = { -27 , -15, -14};
        int step = -1;

        for (int i = 0; i < 3; i++)
        {
            wallEnvImg.SetPosition(CustomMath::PositionToIsoCoordF(indexs[i]));
            wallEnvImg.Draw();
        }

        // Right side
        for (int i = 12; i < 169; i += 13)
        {
            for (int j = 0; j < 13; j++)
            {
                if ((i - j) % 13 == 0 /* || j < 5 */ )
                    continue;
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(i - j));
                wallEnvImg.SetPosition(vector);
                wallEnvImg.Draw();
            }
        }

        // Left side
        for (int i = 104; i > 0; i -= 13)
        {
            for (int j = 0; j < 13; j++)
            {
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(-(i + j)));
                wallEnvImg.SetPosition(vector);
                wallEnvImg.Draw();
            }
        }


    }
    else
    {

        // Right side
        for (int i = 0; i < 14; i++)
        {
            for (int j = 13; j < 21; j++)
            {
                Vector2f vector = CustomMath::EnvPositionToIsoCoordF(i * 21 + j);
                wallEnvImg.SetPosition(vector);
                wallEnvImg.Draw();
            }
        }

        // Left side
        for (int i = 273; i < 441; i += 21) // 20 * 13= 260 , 20*7 + 260=400
        {
            for (int j = 0; j < 20; j++)
            {
                Vector2f vector = CustomMath::EnvPositionToIsoCoordF(i + j);
                wallEnvImg.SetPosition(vector);
                wallEnvImg.Draw();
            }
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
            positionSelection = CustomMath::PositionToIsoCoordF(i);
            grounds[selectedGround].SetPosition(positionSelection);
            grounds[selectedGround].Draw();
        }
    }


	for (int i = 0; i < 169; i++)
	{
        positionSelection = CustomMath::PositionToIsoCoordF(i);

 
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

        if (*(mapBomb + i) >= 0.0f)
        {
            bombImg.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapBomb + i)) + 1) * -5.0f);
            bombImg.SetScale(.3f + sin(*(mapBomb + i) * 2.0f) * 0.01f, .3f + sin(*(mapBomb + i) * 2.0f) * 0.01f);
            bombImg.Draw();
        }

        

        /*if (*(mapCollectable + i) >= 0.0f)
        {
            switch (*(map + i))
            {
                case MapEntity::LifeIt:
                    heartImg.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapCollectable + i)) + 1) * -5.0f);
                    heartImg.Draw();
                    break;
                case MapEntity::BombIt:
                    bombImg2.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapCollectable + i)) + 1) * -5.0f);
                    bombImg2.Draw();
                    break;
                case MapEntity::SpeedIt:
                    speedImg.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapCollectable + i)) + 1) * -5.0f);
                    speedImg.Draw();
                    break;
                default: // PowerIt
                    powerImg.SetPosition(positionSelection.x, positionSelection.y + (sin(*(mapCollectable + i)) + 1) * -5.0f);
                    powerImg.Draw();
                    break;
            }
        }*/

        
        
        if (*(map + i) > MapEntity::Bomb)
        {
            float x = GetPseudoRandom(i);
            switch (*(map + i))
            {
                case MapEntity::LifeIt:
                    heartImg.SetPosition(positionSelection.x, positionSelection.y + (sin(x + *collectableTime) + 1) * -5.0f);
                    heartImg.Draw();
                    break;
                case MapEntity::BombIt:
                    bombImg2.SetPosition(positionSelection.x, positionSelection.y + (sin(x + *collectableTime) + 1) * -5.0f);
                    bombImg2.Draw();
                    break;
                case MapEntity::SpeedIt:
                    speedImg.SetPosition(positionSelection.x, positionSelection.y + (sin(x + *collectableTime) + 1) * -5.0f);
                    speedImg.Draw();
                    break;
                default: // PowerIt
                    powerImg.SetPosition(positionSelection.x, positionSelection.y + (sin(x + *collectableTime) + 1) * -5.0f);
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

float MapDrawer::GetPseudoRandom(int i)
{
    float x = sinf(i / 169.0f) * 10000.0f;
    x = (x - floorf(x)) * 4.0f;

    return x;
}