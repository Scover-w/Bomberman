#include "UIMenuPage.h"


UIMenuPage::UIMenuPage(MenuPage* p)
{
	page = p;

	playBtn.SetBasicProperties(349, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	playBtn.SetImgText("Images/UI/Menu/Play.png");
	playBtn.SetOriginText(25, -55);

	editorBtn.SetBasicProperties(433, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	editorBtn.SetImgText("Images/UI/Menu/Editor.png");
	editorBtn.SetOriginText(45, -40);
}

UIMenuPage::~UIMenuPage()
{

}

void UIMenuPage::Update()
{
	int mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();
	if (playBtn.DoesClick(mouseUIPositionId))
	{
		page->PlayClick();
	}
	if (editorBtn.DoesClick(mouseUIPositionId))
	{
		page->EditorClick();
	}
}

void UIMenuPage::Draw()
{
	playBtn.Draw();
	editorBtn.Draw();
}

void UIMenuPage::DisplayButtons()
{
	playBtn.Enable();
	editorBtn.Enable();
}

void UIMenuPage::HideButtons()
{
	playBtn.Disable();
	editorBtn.Disable();
}