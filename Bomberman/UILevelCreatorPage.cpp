#include "UILevelCreatorPage.h"

UILevelCreatorPage::UILevelCreatorPage(LevelCreatorPage* page1)
{
	page = page1;

	titleImg.SetTexture("Images/UI/LevelCreator/ModeEditeur.png");
	titleImg.SetPosition(40, 250);
	titleImg.SetRotation(-26.5);

	nextPBtn.SetBasicProperties(416, PhysicalButtonType::Square, RotationType::Vertical);
	nextPBtn.SetImgText("Images/UI/LevelCreator/RightPB.png");
	nextPBtn.SetOriginText(24, -15);

	previousPBtn.SetBasicProperties(414, PhysicalButtonType::Square, RotationType::Vertical);
	previousPBtn.SetImgText("Images/UI/LevelCreator/LeftPB.png");
	previousPBtn.SetOriginText(18, -17);

	backMenuPBtn.SetBasicProperties(366, PhysicalButtonType::Square, RotationType::Vertical);
	backMenuPBtn.SetImgText("Images/UI/LevelCreator/LeftPB.png");
	backMenuPBtn.SetOriginText(18, -17);

	savePBtn.SetBasicProperties(656, PhysicalButtonType::Rectangle6, RotationType::Vertical);
	savePBtn.SetImgText("Images/UI/LevelCreator/SavePB.png");
	savePBtn.SetOriginText(50, -38);
	savePBtn.Disable();

	switchModePBtn1.SetBasicProperties(124, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	switchModePBtn1.SetImgText("Images/UI/LevelCreator/EditorModePB.png");
	switchModePBtn1.SetOriginText(41, -39);
	switchModePBtn1.Disable();

	switchModePBtn2.SetBasicProperties(124, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	switchModePBtn2.SetImgText("Images/UI/LevelCreator/NormalModePB.png");
	switchModePBtn2.SetOriginText(41, -39);

	newLevelPBtn.SetBasicProperties(657, PhysicalButtonType::Rectangle3, RotationType::Vertical);
	newLevelPBtn.SetImgText("Images/UI/LevelCreator/CreateTextButton.png");
	newLevelPBtn.SetOriginText(60, -35);
	
	borderLevelImg.SetTexture("Images/UI/LevelCreator/BorderLevel.png");
	borderLevelImg.SetPosition(CustomMath::UM_PositionToIsoCoordF(580));
	borderLevelImg.SetOrigin(0, -3);

	levelTxt.setFont(SelectedFont::instance->GetFont());
	levelTxt.setPosition(CustomMath::UM_PositionToIsoCoordF(581));
	levelTxt.setCharacterSize(50);
	levelTxt.setRotation(-26.5);
}

UILevelCreatorPage::~UILevelCreatorPage()
{

}


void UILevelCreatorPage::SetEditionMode()
{
	switchModePBtn1.Enable();
	switchModePBtn2.Disable();
	savePBtn.Enable();
	newLevelPBtn.Disable();
	previousPBtn.Disable();
	nextPBtn.Disable();
	isEditing = true;
}
void UILevelCreatorPage::SetNormalMode()
{
	switchModePBtn1.Disable();
	switchModePBtn2.Enable();
	savePBtn.Disable();
	newLevelPBtn.Enable();
	previousPBtn.Enable();
	nextPBtn.Enable();
	isEditing = false;
}
void UILevelCreatorPage::SetMaxMapId(int id)
{
	maxMapId = id;
}
void UILevelCreatorPage::SetActualMapId(int id)
{
	selectedMapId = id;
	levelTxt.setString("Level : " + to_string(id));

	if (id <= 1)
		previousPBtn.SetActive(false);
	else
		previousPBtn.SetActive(true);

	if (id >= maxMapId)
		nextPBtn.SetActive(false);
	else
		nextPBtn.SetActive(true);
}


void UILevelCreatorPage::Update()
{
	mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();

	if (nextPBtn.DoesClick(mouseUIPositionId))
		page->UINextLevelClick();

	if (previousPBtn.DoesClick(mouseUIPositionId))
		page->UIPreviousLevelClick();

	if (backMenuPBtn.DoesClick(mouseUIPositionId))
	{
		SetNormalMode();
		page->UIBackMenu();
	}

	if (savePBtn.DoesClick(mouseUIPositionId))
		page->UISaveClick();

	if (switchModePBtn1.DoesClick(mouseUIPositionId) || switchModePBtn2.DoesClick(mouseUIPositionId))
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

	if (newLevelPBtn.DoesClick(mouseUIPositionId))
		page->UICreateLevel();
}
void UILevelCreatorPage::Draw()
{
	titleImg.Draw();
	nextPBtn.Draw();
	previousPBtn.Draw();
	backMenuPBtn.Draw();
	savePBtn.Draw();
	switchModePBtn1.Draw();
	switchModePBtn2.Draw();

	newLevelPBtn.Draw();

	borderLevelImg.Draw();

	StaticWindow::window->draw(levelTxt);
}