#include "UILevelCreatorPage.h"

UILevelCreatorPage::UILevelCreatorPage(LevelCreatorPage* page1)
{
	title.SetTexture("Images/UI/LevelCreator/ModeEditeur.png");
	title.SetPosition(40, 250);
	title.SetRotation(-26.5);

	nextButton.SetTexture("Images/UI/LevelCreator/Right.png");
	nextButton.SetPosition(1800,850);
	nextButton.SetScale(0.5f, .5f);
	previousButton.SetTexture("Images/UI/LevelCreator/Left.png");
	previousButton.SetPosition(1750, 850);
	previousButton.SetScale(0.5f, .5f);
	backMenuButton.SetTexture("Images/UI/LevelCreator/Left.png");
	backMenuButton.SetPosition(-80, -40);
	backMenuButton.SetScale(0.5f, .5f);
	saveButton.SetTexture("Images/UI/LevelCreator/Save.png");
	saveButton.SetPosition(60, 850);
	saveButton.SetScale(0.5f, .5f);
	saveButton.Disable();
	switchModeButton1.SetTexture("Images/UI/LevelCreator/EditionMode.png");
	switchModeButton1.SetPosition(1820, -40);
	switchModeButton1.SetScale(0.5f, .5f);
	switchModeButton1.Disable();
	switchModeButton2.SetTexture("Images/UI/LevelCreator/NormalMode.png");
	switchModeButton2.SetPosition(1820, -40);
	switchModeButton2.SetScale(0.5f, .5f);
	//newLevelButton.SetTexture("Images/UI/LevelCreator/Create.png");
	//newLevelButton.SetPosition(130, 850);
	//newLevelButton.SetScale(0.5f, .5f);

	levelText.setFont(SelectedFont::instance->GetFont());
	levelText.setPosition(1450, 770);
	levelText.setCharacterSize(50);
	levelText.setRotation(-26.5);
	page = page1;

	newLevelPButton.SetTextures("Images/UI/Button/PhysicalButton.png",
								"Images/UI/Button/PhysicalButtonHover.png", 
								"Images/UI/Button/PhysicalButtonClick.png");

	newLevelPButton.SetPositionId(657);
	newLevelPButton.SetOrigin(0.0f, 0.0f);
}

UILevelCreatorPage::~UILevelCreatorPage()
{

}

void UILevelCreatorPage::Update()
{
	mousePosition = MouseTool::GetGlobalPosition();

	mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();

	if (nextButton.DoesClick(mousePosition))
		page->UINextLevelClick();

	if (previousButton.DoesClick(mousePosition))
		page->UIPreviousLevelClick();

	if (backMenuButton.DoesClick(mousePosition))
	{
		SetNormalMode();
		page->UIBackMenu();
	}

	if (saveButton.DoesClick(mousePosition))
		page->UISaveClick();

	if (switchModeButton1.DoesClick(mousePosition) || switchModeButton2.DoesClick(mousePosition))
	{
		isEditing = !isEditing;
		if (isEditing)
		{
			SetEditionMode();
		}
		else
		{
			SetNormalMode();
		}
		page->UISwitchModeClick();
	}

	/*if (newLevelButton.DoesClick(mousePosition))
		page->UICreateLevel();*/

	if (newLevelPButton.DoesClick(mouseUIPositionId))
		cout << "Click" << endl;
}

void UILevelCreatorPage::Draw()
{
	title.Draw();
	nextButton.Draw();
	previousButton.Draw();
	backMenuButton.Draw();
	saveButton.Draw();
	switchModeButton1.Draw();
	switchModeButton2.Draw();
	//newLevelButton.Draw();

	newLevelPButton.Draw();

	StaticWindow::window->draw(levelText);
}

void UILevelCreatorPage::SetEditionMode()
{
	switchModeButton1.Enable();
	switchModeButton2.Disable();
	saveButton.Enable();
	newLevelButton.Disable();
	previousButton.Disable();
	nextButton.Disable();
	isEditing = true;
}

void UILevelCreatorPage::SetNormalMode()
{
	switchModeButton1.Disable();
	switchModeButton2.Enable();
	saveButton.Disable();
	newLevelButton.Enable();
	previousButton.Enable();
	nextButton.Enable();
	isEditing = false;
}

void UILevelCreatorPage::SetMaxMapId(int id)
{
	maxMapId = id;
}

void UILevelCreatorPage::SetActualMapId(int id)
{
	selectedMapId = id;
	levelText.setString("Level : " + to_string(id));

	if (id <= 1)
		previousButton.SetActive(false);
	else
		previousButton.SetActive(true);

	if (id >= maxMapId)
		nextButton.SetActive(false);
	else
		nextButton.SetActive(true);
}