#include "LevelCreatorPage.h"
#include "UILevelCreatorPage.h"

LevelCreatorPage::LevelCreatorPage()
{
    LoadTextures();

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
   

    UILevelCreatorPage* tempUI = new UILevelCreatorPage(this);
    ui = tempUI;
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

    redTest.SetTexture("Images/Editor/RedPoint.png");
    redTest.SetOrigin(5.0f, 5.0f);
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

void LevelCreatorPage::LoadPage()
{
    DataManager::instance->NoFirstLoad();

    isEditing = false;
    selectedMapId = 1;
    maxMapId = MapEditor::GetMaxId();
    MapDrawer::instance->SetMap(map);
    ui->SetMaxMapId(maxMapId);
    ui->SetActualMapId(1);
    ui->SetNormalMode();
}

void LevelCreatorPage::Update()
{
    ui->Update();
    MapDrawer::instance->DrawEnv(true);

    MapDrawer::instance->DrawEditor();

    DrawSelection();

    MapDrawer::instance->DrawEnv(false);

    ManageEvent();

    ui->Draw();

    int temp = MouseTool::UM_GetIndexPositionMouse();
    cout << temp << endl;
    Vector2f positionSelection = CustomMath::UM_PositionToIsoCoordF(temp);
    redTest.SetPosition(positionSelection);
    redTest.Draw();
   
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
        else if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            StaticWindow::window->close();
    }
}

void LevelCreatorPage::MousePressed(Event& e)
{
    if (isEditing)
    {
        if (MouseTool::GM_GetIndexPositionMouse() < 0)
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
    int temp = MouseTool::GM_GetIndexPositionMouse();
    
    if (temp != selectedIndexs[0])
    {
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

        Vector2f positionSelection = CustomMath::GM_PositionToIsoCoordF(selectedIndexs[i]);
        brickWall.SetPosition(positionSelection);
        brickWall.Draw();
    }
}

void LevelCreatorPage::ComputeMirrorSelection()
{
    if (selectedIndexs[0] == 84) // Center of matrice in both axes : N*N / 2
        return;

    if (selectedIndexs[0] % Settings::SIZE_GAME_MAP == 6) // Center of matrice on x axis : N / 2
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
    int middleLineIndex = (index % Settings::SIZE_GAME_MAP) + Settings::SIZE_GAME_MAP * 6;
    return middleLineIndex + middleLineIndex - index;
}

int LevelCreatorPage::MirrorY(int index)
{
    return index - (index % Settings::SIZE_GAME_MAP - 6) * 2;
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
    DataManager::instance->SetCurrentPage(page);
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