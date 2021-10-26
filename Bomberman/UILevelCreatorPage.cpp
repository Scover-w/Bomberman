#include "UILevelCreatorPage.h"

UILevelCreatorPage::UILevelCreatorPage(LevelCreatorPage* page1)
{
	title.SetTexture("Images/UI/LevelCreator/ModeEditeur.png");
	title.SetPosition(40, 250);
	title.SetRotation(-26.5);

	nextPButton.SetBasicProperties(416, PhysicalButtonType::Square, RotationType::Vertical);
	nextPButton.SetImgText("Images/UI/LevelCreator/RightPB.png");
	nextPButton.SetOriginText(24, -15);

	previousPButton.SetBasicProperties(414, PhysicalButtonType::Square, RotationType::Vertical);
	previousPButton.SetImgText("Images/UI/LevelCreator/LeftPB.png");
	previousPButton.SetOriginText(18, -17);

	backMenuPButton.SetBasicProperties(366, PhysicalButtonType::Square, RotationType::Vertical);
	backMenuPButton.SetImgText("Images/UI/LevelCreator/LeftPB.png");
	backMenuPButton.SetOriginText(18, -17);

	savePButton.SetBasicProperties(656, PhysicalButtonType::Rectangle6, RotationType::Vertical);
	savePButton.SetImgText("Images/UI/LevelCreator/SavePB.png");
	savePButton.SetOriginText(50, -38);
	savePButton.Disable();

	switchModePButton1.SetBasicProperties(124, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	switchModePButton1.SetImgText("Images/UI/LevelCreator/EditorModePB.png");
	switchModePButton1.SetOriginText(41, -39);
	switchModePButton1.Disable();

	switchModePButton2.SetBasicProperties(124, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	switchModePButton2.SetImgText("Images/UI/LevelCreator/NormalModePB.png");
	switchModePButton2.SetOriginText(41, -39);

	newLevelPButton.SetBasicProperties(657, PhysicalButtonType::Rectangle3, RotationType::Vertical);
	newLevelPButton.SetImgText("Images/UI/LevelCreator/CreateTextButton.png");
	newLevelPButton.SetOriginText(60, -35);
	
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

	mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();

	if (nextPButton.DoesClick(mouseUIPositionId))
		page->UINextLevelClick();

	if (previousPButton.DoesClick(mouseUIPositionId))
		page->UIPreviousLevelClick();

	if (backMenuPButton.DoesClick(mouseUIPositionId))
	{
		SetNormalMode();
		page->UIBackMenu();
	}

	if (savePButton.DoesClick(mouseUIPositionId))
		page->UISaveClick();

	if (switchModePButton1.DoesClick(mouseUIPositionId) || switchModePButton2.DoesClick(mouseUIPositionId))
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

	if (newLevelPButton.DoesClick(mouseUIPositionId))
		page->UICreateLevel();
}

void UILevelCreatorPage::Draw()
{
	title.Draw();
	nextPButton.Draw();
	previousPButton.Draw();
	backMenuPButton.Draw();
	savePButton.Draw();
	switchModePButton1.Draw();
	switchModePButton2.Draw();

	newLevelPButton.Draw();

	StaticWindow::window->draw(levelText);
}

void UILevelCreatorPage::SetEditionMode()
{
	switchModePButton1.Enable();
	switchModePButton2.Disable();
	savePButton.Enable();
	newLevelPButton.Disable();
	previousPButton.Disable();
	nextPButton.Disable();
	isEditing = true;
}

void UILevelCreatorPage::SetNormalMode()
{
	switchModePButton1.Disable();
	switchModePButton2.Enable();
	savePButton.Disable();
	newLevelPButton.Enable();
	previousPButton.Enable();
	nextPButton.Enable();
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
		previousPButton.SetActive(false);
	else
		previousPButton.SetActive(true);

	if (id >= maxMapId)
		nextPButton.SetActive(false);
	else
		nextPButton.SetActive(true);
}