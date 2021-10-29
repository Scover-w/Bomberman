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
#include "SoundManager.h"

int main()
{
    RenderWindow window(sf::VideoMode(Settings::SIZE_SCREEN.x, Settings::SIZE_SCREEN.y), "Bomberman", sf::Style::Fullscreen); // 50px per images

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

    SoundManager soundManager;

    CursorManager cursorManager;

    Timer timer;

    Page currentPage = Page::Start;
    DataManager dataManager;

    dataManager.SetCurrentPage(currentPage);

    View view(FloatRect(0, 0, Settings::SIZE_SCREEN.x, Settings::SIZE_SCREEN.y));
    view.zoom(Settings::ZOOM);
    window.setView(view);

    Texture texture;
    texture.create(Settings::SIZE_SCREEN.x, Settings::SIZE_SCREEN.y);

    Clock clk;

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
- delta to compensate : setorigin wall black
- ui partout
- son
- gestion jeu : 1, 2,3 etc
- ia
- seamless between Menu and Game with transition shader : passing time to get seamless shader
   -> fade out  //texture.update(window);
*/