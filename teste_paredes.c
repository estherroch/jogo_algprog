

#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 600
#define ALTURA 600
#define LADO 20
#define MAX_INIMIGOS 10

// Defina o tamanho do mapa (número de células em largura e altura)
#define MAPA_LARGURA (LARGURA / LADO)
#define MAPA_ALTURA (ALTURA / LADO)

// Function to place continuous walls in the map with an opening
void placeContinuousWallsWithOpening(int startX, int startY, int endX, int endY, int openingX, int openingY, int mapa[MAPA_LARGURA][MAPA_ALTURA]) {

    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

    for (int x = startX; x != endX + stepX; x += stepX) {
        for (int y = startY; y != endY + stepY; y += stepY) {
            if (x >= 0 && x < MAPA_LARGURA && y >= 0 && y < MAPA_ALTURA && (x != openingX || y != openingY)) {
                mapa[x][y] = 1;
            }
        }
    }
}

int main(void) {
    int mapa[MAPA_LARGURA][MAPA_ALTURA] = {0};

    // Place continuous walls with openings
    for (int i = 0; i < LARGURA; i++) {
        if (i == 3 || i == 10 || i == 17) {  // Three vertical wall positions
            placeContinuousWallsWithOpening(i, 2, i, ALTURA / LADO - 4, i, LADO / 2, mapa);

        }
    }

    for (int i = 0; i < ALTURA; i++) {
        if (i == 5 || i == 12) {  // Three horizontal wall positions
            placeContinuousWallsWithOpening(i, i, LARGURA / LADO - 4, i, i, 6, mapa);
        }
    }

    // Initialize the window
    InitWindow(LARGURA, ALTURA, "Placing Continuous Walls with Opening Example");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the map
        for (int y = 0; y < MAPA_ALTURA; y++) {
            for (int x = 0; x < MAPA_LARGURA; x++) {
                Rectangle rect = {x * LADO, y * LADO, LADO, LADO};
                if (mapa[x][y] == 1) {
                    DrawRectangleRec(rect, DARKGRAY);  // Wall
                } else {
                    DrawRectangleRec(rect, RAYWHITE);  // Open path
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

