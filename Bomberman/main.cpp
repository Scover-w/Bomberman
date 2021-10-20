#include "headersProject.h"
#include "StartPage.h"
#include "MenuPage.h"
#include "InstructionPage.h"
#include "GamePage.h"
#include "LevelCreatorPage.h"
#include "EndPage.h"
#include "Settings.h"
#include "CustomMath.h"
#include "MapDrawer.h"
#include "CursorManager.h"

int main()
{
    RenderWindow window(sf::VideoMode(Settings::WIDTH_SCREEN, Settings::HEIGHT_SCREEN), "Bomberman"/*, sf::Style::Fullscreen*/); // 50px per images

    StaticWindow staticWindow;
    staticWindow.window = &window;

    CustomRandom cRandom;
    SelectedFont selectedFont;
    MapDrawer mapDrawer;

    MouseTool mouseTool;
    StartPage startPage;
    MenuPage menuPage;
    InstructionPage instructionPage;
    GamePage gamePage;
    LevelCreatorPage levelCreatorPage;
    EndPage endPage;

    CursorManager cursorManager;

    Timer timer;

    Page currentPage = Page::Start;
    DataManager dataManager;

    dataManager.SetCurrentPage(currentPage);

    sf::View view(sf::FloatRect(0, 0, Settings::WIDTH_SCREEN, Settings::HEIGHT_SCREEN));
    view.zoom(1.1f);
    window.setView(view);


    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        timer.SetDeltaTime();

        switch (dataManager.GetCurrentPage())
        {
            case Page::Game:
                if (DataManager::instance->IsFirstLoad())
                    gamePage.LoadPage();
                gamePage.Update();
                break;
            case Page::Menu:
                if (DataManager::instance->IsFirstLoad())
                    menuPage.LoadPage();
                menuPage.Update();
                break;
            case Page::Instructions:
                if (DataManager::instance->IsFirstLoad())
                    instructionPage.LoadPage();
                instructionPage.Update();
                break;
            case Page::LevelCreator:
                if (DataManager::instance->IsFirstLoad())
                    levelCreatorPage.LoadPage();
                levelCreatorPage.Update();
                break;
            case Page::Start:
                if (DataManager::instance->IsFirstLoad())
                    startPage.LoadPage();
                startPage.Update();
                break;
            case Page::End:
                if (DataManager::instance->IsFirstLoad())
                    endPage.LoadPage();
                endPage.Update();
                break;
        }

        window.display();    
    }

    return 0;

}
 
/* 
TO DO :
- box bomb wall if propritary
- ui partout
- shadow ?
- son
- gestion jeu : 1, 2,3 etc
- ia
*/