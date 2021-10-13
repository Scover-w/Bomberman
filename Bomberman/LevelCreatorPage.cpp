#include "LevelCreatorPage.h"
#include "UILevelCreatorPage.h"

LevelCreatorPage::LevelCreatorPage()
{
    LoadTextures();
 
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
    maxMapId = MapEditor::GetMaxId();

    MapDrawer::instance->SetMap(map);

    UILevelCreatorPage* tempUI = new UILevelCreatorPage(this);
    ui = tempUI;

    ui->SetMaxMapId(maxMapId);
    ui->SetActualMapId(1);
}

LevelCreatorPage::~LevelCreatorPage()
{
    free(ui);
}

void LevelCreatorPage::LoadTextures()
{
    opaque = sf::Color(255, 255, 255, 255);
    midtransparent = sf::Color(255, 255, 255, 185);
    transparent = sf::Color(255, 255, 255, 50);

    selectionImg.SetTexture("Images/Editor/selection.png");
    selectionImg.SetOrigin(80, 0);

    unSelectionImg.SetTexture("Images/Editor/unSelection.png");
    unSelectionImg.SetOrigin(80, 0);

    groundImg.SetTexture("Images/Grounds/autumn.png");
    groundImg.SetOrigin(80, 0);

    wallImg.SetTexture("Images/Walls/BlackBrick.png");
    wallImg.SetOrigin(80, 37);

    brickWall.SetTexture("Images/Walls/BrickAlt1.png");
    brickWall.SetOrigin(80, 37);
    brickWall.SetColor(transparent);
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
            wallImg.SetPosition(CustomMath::PositionToIsoCoordF(indexs[i]));
            wallImg.Draw();
        }

        // Right side
        for (int i = 12; i < 169; i += 13)
        {
            for (int j = 0; j < 13; j++)
            {
                if ((i - j ) % 13 == 0 || j < 5)
                    continue;
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(i - j));
                wallImg.SetPosition(vector);
                wallImg.Draw();
            }   
        }

        // Left side
        for (int i = 91; i > 0; i -= 13)
        {
            for (int j = 0; j < 13; j++)
            {
                Vector2f vector = CustomMath::EnvCartesianToIsometric(CustomMath::PositionToCartCoordF(-(i + j)));
                wallImg.SetPosition(vector);
                wallImg.Draw();
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
                wallImg.SetPosition(vector);
                wallImg.Draw();
            }
        }
        
        // Left side
        for (int i = 273; i < 441; i += 21) // 20 * 13= 260 , 20*7 + 260=400
        {
            for (int j = 0; j < 20; j++)
            {
                Vector2f vector = CustomMath::EnvPositionToIsoCoordF(i + j);
                wallImg.SetPosition(vector);
                wallImg.Draw();
            }
        }
    }
    
}

void LevelCreatorPage::SwitchEditing()
{
    isEditing = !isEditing;

    brickWall.SetColor(isEditing ? midtransparent : transparent);
}

bool LevelCreatorPage::CanEdit()
{
    return isEditing;
}

void LevelCreatorPage::Update()
{
    ui->Update();
    DrawBackEnv(true);

    for (int i = 0; i < 169; i++)
    {
        groundImg.SetPosition(CustomMath::PositionToIsoCoordF(i));
        groundImg.Draw();
    }


    MapDrawer::instance->Draw();

    DrawSelection();

    DrawBackEnv(false);

    ManageEvent();

    ui->Draw();
}

void LevelCreatorPage::ManageEvent()
{
    Event event;
    while (StaticWindow::window->pollEvent(event))
    {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::M)
            SwitchEditing();
        else if (event.type == Event::MouseButtonPressed)
            MousePressed(event);
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
        //cout << "Index : " << temp << endl;
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
        brickWall.SetPosition(positionSelection);
        brickWall.Draw();
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

        map[selectedIndexs[i]] = MapEntity::Wall;
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

        map[selectedIndexs[i]] = MapEntity::None;
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


void LevelCreatorPage::UISaveClick()
{
    MapEditor::WriteMap(selectedMapId, map);

    SwitchEditing();
    ui->SetNormalMode();
}

void LevelCreatorPage::UINextLevelClick()
{
    selectedMapId++;
    if (selectedMapId > maxMapId)
        selectedMapId = maxMapId;

    MapEditor::LoadMap(selectedMapId, map);
    ui->SetActualMapId(selectedMapId);
}

void LevelCreatorPage::UIPreviousLevelClick()
{
    selectedMapId--;
    if (selectedMapId < 1)
        selectedMapId = 1;

    MapEditor::LoadMap(selectedMapId, map);
    ui->SetActualMapId(selectedMapId);

}

void LevelCreatorPage::UISwitchModeClick()
{
    SwitchEditing();
}

void LevelCreatorPage::UIBackMenu()
{
    Page page = Page::Menu;
    DataManager::dataManager->SetCurrentPage(page);
}

void LevelCreatorPage::UICreateLevel()
{
    for (int i = 0; i < 169; i++)
    {
        map[i] = MapEntity::None;
    }

    maxMapId++;
    selectedMapId = maxMapId;
    ui->SetMaxMapId(maxMapId);
    ui->SetActualMapId(maxMapId);
    SwitchEditing();
    ui->SetEditionMode();
}