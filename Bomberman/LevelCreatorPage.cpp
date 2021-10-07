#include "LevelCreatorPage.h"


LevelCreatorPage::LevelCreatorPage()
{
    if (selectionT.loadFromFile("Images/Editor/selection.png"))
    {
        selectionS.setTexture(selectionT);
        selectionT.setSmooth(true);

        selectionS.setOrigin(80, 0);
    }

    if (unselectionT.loadFromFile("Images/Editor/unSelection.png"))
    {
        unselectionS.setTexture(unselectionT);
        unselectionT.setSmooth(true);

        unselectionS.setOrigin(80, 0);
    }

    if (groundT.loadFromFile("Images/Grounds/autumn.png"))
    {
        groundS.setTexture(groundT);
        groundT.setSmooth(true);
        groundS.setOrigin(80, 0);
    }

    if (wallT.loadFromFile("Images/Walls/BlackBrick.png"))
    {
        wallS.setTexture(wallT);
        wallT.setSmooth(true);
        wallS.setOrigin(80, 37);
    }

    opaque = sf::Color(255, 255, 255, 255);
    midtransparent = sf::Color(255, 255, 255, 185);
    transparent = sf::Color(255, 255, 255, 50);

    if (mapEntitiesT[0].loadFromFile("Images/Walls/BrickAlt1.png"))
    {
        mapEntitiesS[0].setTexture(mapEntitiesT[0]);
        mapEntitiesT[0].setSmooth(true);
        mapEntitiesS[0].setOrigin(80, 37);
    }
    if (mapEntitiesT[1].loadFromFile("Images/Destructible/RedRuby.png"))
    {
        mapEntitiesS[1].setTexture(mapEntitiesT[1]);
        mapEntitiesT[1].setSmooth(true);
        mapEntitiesS[1].setOrigin(80, 37);
    }

    mapEntitiesS[0].setColor(transparent);
    mapEntitiesS[1].setColor(transparent);

    Vector2i tempVector(0, 0);
    isEditing = false;

    if (MapEditor::DoesMapExist(1))
    {
        MapEditor::LoadMap(1, map);
    }
    else
    {
        for (int i = 0; i < 169; i++)
        {
            map[i] = MapEntity::None;
        }

        MapEditor::WriteMap(1, map);
    }
    selectedMapId = 1;

    MapDrawer::instance->SetMap(map);

}

LevelCreatorPage::~LevelCreatorPage()
{

}

void LevelCreatorPage::DrawBackEnv(bool isFirstPart)
{
    if (isFirstPart)
    {
        // Mirror up
        int indexs[] = { -39, -26, -14, -13, -3, -2, -1};
        int step = -1;
        
        for (int i = 0; i < 7; i++)
        {
            wallS.setPosition(CustomMath::PositionToIsoCoordF(indexs[i]));
            StaticWindow::window->draw(wallS);
        }

        // Right side
        for (int i = 12; i < 169; i += 13)
        {
            for (int j = 0; j < 13; j++)
            {
                if ((i - j ) % 13 == 0 || j < 5)
                    continue;
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(i - j));
                wallS.setPosition(vector);
                StaticWindow::window->draw(wallS);
            }   
        }

        // Left side
        for (int i = 91; i > 0; i -= 13)
        {
            for (int j = 0; j < 13; j++)
            {
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(-(i + j)));
                wallS.setPosition(vector);
                StaticWindow::window->draw(wallS);
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
                Vector2f vector = CustomMath::EnvPositionToIsoCoordF(i* 21 + j);
                wallS.setPosition(vector);
                StaticWindow::window->draw(wallS);
            }
        }
        
        // Left side
        for (int i = 273; i < 441; i += 21) // 20 * 13= 260 , 20*7 + 260=400
        {
            for (int j = 0; j < 20; j++)
            {
                Vector2f vector = CustomMath::EnvPositionToIsoCoordF(i + j);
                wallS.setPosition(vector);
                StaticWindow::window->draw(wallS);
            }
        }
    }
    
}


void LevelCreatorPage::SwitchEditing()
{
    isEditing = !isEditing;

    mapEntitiesS[0].setColor(isEditing ? midtransparent : transparent);
    mapEntitiesS[1].setColor(isEditing ? midtransparent : transparent);
}

bool LevelCreatorPage::CanEdit()
{
    return isEditing;
}

void LevelCreatorPage::Update()
{
    DrawBackEnv(true);

    for (int i = 0; i < 169; i++)
    {
        groundS.setPosition(CustomMath::PositionToIsoCoordF(i));
        StaticWindow::window->draw(groundS);
    }


    MapDrawer::instance->Draw();

    DrawSelection();

    DrawBackEnv(false);

    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::M)
            SwitchEditing();
        else if(event.type ==  Event::MouseButtonPressed)
            MousePressed(event);
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            selectedMapEntity += event.mouseWheel.delta;
            selectedMapEntity = selectedMapEntity % 2;
        }
        else if (event.type == Event::Closed)
            StaticWindow::window->close();
    }
}


void LevelCreatorPage::MousePressed(Event& e)
{
    if (isEditing)
    {
        if (MouseTool::GetIndexPositionMouse() < 0)
            ClickUI(e);
        else
            ClickMap(e);  
    }
}

void LevelCreatorPage::ClickMap(Event& e)
{
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        AddEntity();
    }
    else if(Mouse::isButtonPressed(Mouse::Right))
    {
        RemoveEntity();
    }
    else if (Mouse::isButtonPressed(Mouse::Middle))
    {
        cout << "Middle mouse" << endl;
    }
}

void LevelCreatorPage::ClickUI(Event& e)
{

}

void LevelCreatorPage::DrawSelection()
{
    int temp = MouseTool::GetIndexPositionMouse();

    if (temp != selectedIndexs[0])
    {
        cout << "Index : " << temp << endl;
        for (int i = 0; i < 4; i++)
        {
            selectedIndexs[i] = -1;
        }

        selectedIndexs[0] = temp;
        ComputeMirrorSelection();
    }

    for (int i = 0; i < 4; i++)
    {
        if (selectedIndexs[i] == -1)
            break;

        Vector2f positionSelection = CustomMath::PositionToIsoCoordF(selectedIndexs[i]);
        if (selectedMapEntity)
        {
            mapEntitiesS[0].setPosition(positionSelection);
            StaticWindow::window->draw(mapEntitiesS[0]);
        }
        else
        {
            mapEntitiesS[1].setPosition(positionSelection);
            StaticWindow::window->draw(mapEntitiesS[1]);
        }
    }
}

void LevelCreatorPage::ComputeMirrorSelection()
{
    if (selectedIndexs[0] == 84) // Center of matrice in both axes : N*N / 2
        return;

    if (selectedIndexs[0] % Settings::NB_HEIGHT_MAP == 6) // Center of matrice on x axis : N / 2
    {
        selectedIndexs[1] = MirrorX(selectedIndexs[0]);
        return;
    }

    if (selectedIndexs[0] >=  78 && selectedIndexs[0] <= 90) // Center of matrice on y axis : 13 * 6 = 78 and 13*7 - 1 = 90
    {
        selectedIndexs[1] = MirrorY(selectedIndexs[0]);
        return;
    }

    // Double mirror
    selectedIndexs[1] = MirrorX(selectedIndexs[0]);
    selectedIndexs[2] = MirrorY(selectedIndexs[0]);
    selectedIndexs[3] = MirrorY(selectedIndexs[1]);

}

int LevelCreatorPage::MirrorX(int index)
{
    int middleLineIndex = (index % Settings::NB_HEIGHT_MAP) + Settings::NB_HEIGHT_MAP * 6;
    return middleLineIndex + middleLineIndex - index;
}

int LevelCreatorPage::MirrorY(int index)
{
    return index - (index % Settings::NB_HEIGHT_MAP - 6) * 2;
}

void LevelCreatorPage::AddEntity()
{
    if (!IsPlacable())
        return;

    for (int i = 0; i < 4; i++)
    {
        if (selectedIndexs[i] == -1)
            return;

        map[i] = selectedMapEntity ? MapEntity::Wall : MapEntity::DBlock;
    }
}

void LevelCreatorPage::RemoveEntity()
{
    if (!IsPlacable())
        return;

    for (int i = 0; i < 4; i++)
    {
        if (selectedIndexs[i] == -1)
            return;

        map[i] = MapEntity::None;
    }
}

bool LevelCreatorPage::IsPlacable()
{
    for (int i = 0; i < 4; i++)
    {
        if (selectedIndexs[i] == -1)
            return true;

        for (int j = 0; j < 12; j++)
        {
            if (selectedIndexs[i] == unPlacableIndex[j])
                return false;
        }
    }
}