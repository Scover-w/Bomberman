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

int main()
{
    RenderWindow window(sf::VideoMode(Settings::WIDTH_SCREEN, Settings::HEIGHT_SCREEN), "Bomberman"); // 50px per images

    StaticWindow staticWindow;
    staticWindow.window = &window;

    MapDrawer mapDrawer;

    StartPage startPage;
    MenuPage menuPage;
    InstructionPage instructionPage;
    GamePage gamePage;
    LevelCreatorPage levelCreatorPage;
    EndPage endPage;

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
            case Page::Start:
                startPage.Update();
                break;
            case Page::Menu:
                menuPage.Update();
                break;
            case Page::Instructions:
                instructionPage.Update();
                break;
            case Page::Game:
                gamePage.Update();
                break;
            case Page::End:
                endPage.Update();
                break;
            case Page::LevelCreator:
                levelCreatorPage.Update();
                break;
        }

        window.display();    
    }

    return 0;

}
 
/* 
TO DO :
- view zoom, get mapPixelToCoords()
- bombe
- collision
- gestion jeu : 1, 2,3 etc
- item
*/