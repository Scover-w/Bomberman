#include "UIMenuPage.h"


UIMenuPage::UIMenuPage(MenuPage* p)
{
	page = p;

	playPBtn.SetBasicProperties(349, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	playPBtn.SetImgText("Images/UI/Menu/Play.png");
	playPBtn.SetOriginText(25, -55);

	editorPBtn.SetBasicProperties(433, PhysicalButtonType::Rectangle4, RotationType::Vertical);
	editorPBtn.SetImgText("Images/UI/Menu/Editor.png");
	editorPBtn.SetOriginText(45, -40);
}
UIMenuPage::~UIMenuPage()
{

}


void UIMenuPage::DisplayButtons()
{
	playPBtn.Enable();
	editorPBtn.Enable();
}
void UIMenuPage::HideButtons()
{
	playPBtn.Disable();
	editorPBtn.Disable();
}


void UIMenuPage::Update()
{
	int mouseUIPositionId = MouseTool::UM_GetIndexPositionMouse();
	if (playPBtn.DoesClick(mouseUIPositionId))
	{
		page->PlayClick();
	}
	if (editorPBtn.DoesClick(mouseUIPositionId))
	{
		page->EditorClick();
	}
}
void UIMenuPage::Draw()
{
	playPBtn.Draw();
	editorPBtn.Draw();
}