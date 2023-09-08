#include "raylib.h"


typedef enum // Menu
{
    newGame,
    loadGame,
    exitGame,
    resume,
    goBack,
    saveGame

} MENU_OPTIONS;


//=======================================================================================================================================================//


void DrawMenu(MENU_OPTIONS currentOption) {

    ClearBackground(RAYWHITE);


    DrawText("LUTECA'S DUNGEON", GetScreenWidth() / 2 - MeasureText("LUTECA'S DUNGEON", 40) / 2, 120, 50, PURPLE);


    if (currentOption == newGame)
        DrawText("> New Game ", GetScreenWidth() / 2 - MeasureText("> New Game", 20) / 2, GetScreenHeight() / 2 - 20, 20, GRAY);
    else
        DrawText("New Game", GetScreenWidth() / 2 - MeasureText("New Game", 20) / 2, GetScreenHeight() / 2 - 20, 20, DARKGRAY);


    if (currentOption == loadGame)
        DrawText("> Load Game ", GetScreenWidth() / 2 - MeasureText("> Load Game", 20) / 2, GetScreenHeight() / 2, 20, GRAY);
    else
        DrawText("Load Game", GetScreenWidth() / 2 - MeasureText("Load Game", 20) / 2, GetScreenHeight() / 2, 20, DARKGRAY);


    if (currentOption == exitGame)
        DrawText("> Exit ", GetScreenWidth() / 2 - MeasureText("> Exit", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
    else
        DrawText("Exit", GetScreenWidth() / 2 - MeasureText("Exit", 20) / 2, GetScreenHeight() / 2 + 20, 20, DARKGRAY);
}

//=======================================================================================================================================================//

void displayMenu() { //aqui era pra ser alguma coisa pra aparecer no meio do jogo

    ClearBackground(RAYWHITE);


    DrawText("THE GAME IS PAUSED", GetScreenWidth() / 2 - MeasureText("JOGO PAUSADO", 40) / 2, 120, 50, PURPLE);
    DrawText("What do you want to do next?", GetScreenWidth() / 2 - MeasureText("What do you want to do next?", 40) / 2, 140, 50, PURPLE);


    DrawText("Start new game - press N", GetScreenWidth() / 2 - MeasureText("Start new game - press N", 20) / 2, GetScreenHeight() / 2 - 20, 20, GRAY);

    DrawText("Load previous game - press C", GetScreenWidth() / 2 - MeasureText("Load previous game - press C", 20) / 2, GetScreenHeight() / 2, 20, BLACK);

    DrawText("Quit - press Q ", GetScreenWidth() / 2 - MeasureText("> Exit", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);

    DrawText("Save current game - press S", GetScreenWidth() / 2 - MeasureText("Save current game - press S", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);

    DrawText("Resume - press V", GetScreenWidth() / 2 - MeasureText("Save current game - press S", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);












