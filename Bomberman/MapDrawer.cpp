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
}

MapDrawer::~MapDrawer()
{

}

void MapDrawer::SetMap(MapEntity(&map2)[169], bool isEditor)
{
	map = map2;

    if (isEditor)
    {
        selectedWall = 0;
        selectedDestructable = 0;
        selectedGround = 0;
    }
    else
    {
        selectedWall = CustomRandom::GetRandom(0, 4);
        selectedDestructable = CustomRandom::GetRandom(0, 14);
        selectedGround = CustomRandom::GetRandom(0, 16);
    }
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
        if (*(map + i) == MapEntity::None)
        {
            positionSelection = CustomMath::PositionToIsoCoordF(i);
            grounds[selectedGround].SetPosition(positionSelection);
            grounds[selectedGround].Draw();
        }
    }

	for (int i = 0; i < 169; i++)
	{
        switch (*(map + i))
        {
            /*case MapEntity::None:
                positionSelection = CustomMath::PositionToIsoCoordF(i);
                grounds[selectedGround].SetPosition(positionSelection);
                grounds[selectedGround].Draw();
                break;*/

            case MapEntity::Wall:
                positionSelection = CustomMath::PositionToIsoCoordF(i);
                walls[selectedWall].SetPosition(positionSelection);
                walls[selectedWall].Draw();
                break;

            case MapEntity::DBlock:
                positionSelection = CustomMath::PositionToIsoCoordF(i);
                destructables[selectedDestructable].SetPosition(positionSelection);
                destructables[selectedDestructable].Draw();
                break;

            case MapEntity::Bomb:

                break;

            case MapEntity::Item:

                break;
        }

        if (player->GetPositionIndex() == i)
        {
            cout << player->GetPositionIndex() << endl;
            player->Draw();
        }
	}
}