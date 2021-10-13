#include "UILevelCreatorPage.h"

UILevelCreatorPage::UILevelCreatorPage(LevelCreatorPage* page1)
{
	title.SetTexture("Images/UI/ModeEditeur.png");
	title.SetPosition(40, 250);
	title.SetRotation(-26.5);

	nextButton.SetTexture("Images/UI/Right.png");
	nextButton.SetPosition(1800,850);
	nextButton.SetScale(0.5f, .5f);
	previousButton.SetTexture("Images/UI/Left.png");
	previousButton.SetPosition(1750, 850);
	previousButton.SetScale(0.5f, .5f);
	backMenuButton.SetTexture("Images/UI/Left.png");
	backMenuButton.SetPosition(-80, -40);
	backMenuButton.SetScale(0.5f, .5f);
	saveButton.SetTexture("Images/UI/Save.png");
	saveButton.SetPosition(60, 850);
	saveButton.SetScale(0.5f, .5f);
	saveButton.Disable();
	switchModeButton1.SetTexture("Images/UI/EditionMode.png");
	switchModeButton1.SetPosition(1820, -40);
	switchModeButton1.SetScale(0.5f, .5f);
	switchModeButton1.Disable();
	switchModeButton2.SetTexture("Images/UI/NormalMode.png");
	switchModeButton2.SetPosition(1820, -40);
	switchModeButton2.SetScale(0.5f, .5f);
	newLevelButton.SetTexture("Images/UI/Create.png");
	newLevelButton.SetPosition(130, 850);
	newLevelButton.SetScale(0.5f, .5f);

	levelText.setFont(SelectedFont::instance->GetFont());
	levelText.setPosition(1450, 770);
	levelText.setCharacterSize(50);
	levelText.setRotation(-26.5);
	page = page1;
}

UILevelCreatorPage::~UILevelCreatorPage()
{

}

void UILevelCreatorPage::Update()
{
	mousePosition = MouseTool::GetGlobalPosition();

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



	if (newLevelButton.DoesClick(mousePosition))
		page->UICreateLevel();
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
	newLevelButton.Draw();

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