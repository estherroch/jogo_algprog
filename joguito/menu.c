#include "raylib.h"


typedef enum // Menu
{
    newGame,
    loadGame,
    exitGame,
} MENU_OPTIONS;


//=======================================================================================================================================================//


void DrawMenu(MENU_OPTIONS currentOption) {

    ClearBackground(RAYWHITE);

    // Draw the game title in the center of the screen.
    DrawText("SAIA VIVO DO LABIRINTO", GetScreenWidth() / 2 - MeasureText("SAIA VIVO DO LABIRINTO", 40) / 2, 120, 50, PURPLE);

    // Check if the current option is "New Game" and draw it highlighted or not.
    if (currentOption == newGame)
        DrawText("> New Game <", GetScreenWidth() / 2 - MeasureText("> New Game <", 20) / 2, GetScreenHeight() / 2 - 20, 20, GRAY);
    else
        DrawText("New Game", GetScreenWidth() / 2 - MeasureText("New Game", 20) / 2, GetScreenHeight() / 2 - 20, 20, DARKGRAY);

    // Check if the current option is "Load Game" and draw it highlighted or not.
    if (currentOption == loadGame)
        DrawText("> Load Game <", GetScreenWidth() / 2 - MeasureText("> Load Game <", 20) / 2, GetScreenHeight() / 2, 20, GRAY);
    else
        DrawText("Load Game", GetScreenWidth() / 2 - MeasureText("Load Game", 20) / 2, GetScreenHeight() / 2, 20, DARKGRAY);

    // Check if the current option is "Exit" and draw it highlighted or not.
    if (currentOption == exitGame)
        DrawText("> Exit <", GetScreenWidth() / 2 - MeasureText("> Exit <", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
    else
        DrawText("Exit", GetScreenWidth() / 2 - MeasureText("Exit", 20) / 2, GetScreenHeight() / 2 + 20, 20, DARKGRAY);
}
